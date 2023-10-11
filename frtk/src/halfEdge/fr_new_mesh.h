//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2023
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef FR_NEW_MESH_H
#define FR_NEW_MESH_H

#include<../src/frtk.h>
#include<../src/fr_core.h>
#include<../vendor/glm/glm/glm.hpp>
#include<../src/fr_transform.h>
#include<../src/halfedge/fr_genID.h>
#include<../src/halfEdge/fr_new_mesh.h>



class Shape;  //Object container for any 2D or 3D shape
struct mesh_halfedge;
struct mesh_face;
struct mesh_edge;
struct mesh_vertex;



struct mesh_face {
    unsigned long     ID;  //face ID
    struct Shape* fsolid=NULL;
    struct mesh_halfedge* hedge=NULL;    //first half edge in the face
    bool       visible;
    bool       selected;

    struct mesh_face* next =NULL;
    struct mesh_face* prev =NULL;
};
//Not sure if we need this 2023-10-11
//struct mesh_edge {
//    unsigned long ID;   //edge ID
//    struct mesh_halfEdge* he1=NULL;
//    bool visible;
//    bool selected;
//};

struct mesh_halfedge {

    struct mesh_halfedge* twin=NULL; //Reverse half edge
    struct mesh_vertex* vertex=NULL;
    struct mesh_face* face = NULL;

    struct mesh_halfedge* next=NULL;
    struct mesh_halfedge* prev=NULL;
};

struct mesh_vertex {
    struct mesh_halfedge* vedge = NULL;
    glm::vec3 vertex=glm::vec3(0.0,0.0,0.0);
    bool      visible = NULL;
};

  

class Shape {
public:
    /**
     * Default Constructor
     * Receives the path to the .off file
     * throws runtime_error if there is any io error or opengl error
     */
    Shape(const std::string& path);

    /**
    *   This will be used to create an instance of the mesh without a file.
    *  Data should be entered to the class using SetVertex
    */
    Shape();

    /**
     * Destructor
     */
    ~Shape();
    /**
    *   Construct the helf-edged data structre for the shape
    
    */
    int build();

    /**
     * Draws the shape
     */
    void Draw();

    /**
     * Obtains the mesh information
     */
    void GetMesh(std::vector<float>& vertices, std::vector<float>& normals,
        std::vector<unsigned int>& indices);

    /**
    *   Set the mesh information
    */
    void SetVertexes(std::vector<float>& vertices, std::vector<unsigned int>& indices);

    void SetNormalizeMesh(bool value);
    bool getNormalizeMesh();

private:
    /**
     * Receives an index and returns the vertex
     */
    glm::vec3 GetVertex(unsigned int index, const float vertices[]);

    /**
     * Receives an index and sets the vertice
     */
    void SetVertex(unsigned int index, float vertices[],
        const glm::vec3& vertex);

    /**
     * Reads the vertex information and the point information from file
     */
    void ReadFile(const std::string& path, std::vector<float>& vertices,
        std::vector<float>& normals, std::vector<unsigned int>& indices);

    /**
     * Reads a .off file
     */
    void ReadOFF(const std::string& path, std::vector<float>& vertices,
        std::vector<unsigned int>& indices);

    /**
     * Reads a .msh file
     */
    void ReadMSH(const std::string& path, std::vector<float>& vertices,
        std::vector<float>& normals, std::vector<unsigned int>& indices);

    /**
     * Normalize the mesh in the range -0.5, 0.5 and center it in 0, 0, 0
     */
    void NormalizeVertices(std::vector<float>& vertices);

    /**
     * Calculate the normals based on the triangles
     */
    void CalculateNormals(const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        std::vector<float>& normals);

    /**
     * Creates the vertex buffer object
     */
    void InitializeVBO(const std::vector<float>& vertices,
        const std::vector<float>& normals,
        const std::vector<unsigned int> indices);
public:
    unsigned int id;        //Each shape has a unique ID
    std::vector<std::shared_ptr<struct mesh_face>> FaceObjects; //Hold all faces for the shape and all other elements


public: 
    /**
    *   Use this to update the verticies that will be drawn by OpenGL.
    *   This must be done after any manupulation.
    */
    int updateVerticies(void);

private:
    std::vector<float> vertices_;
    std::vector<float> normals_;
    std::vector<unsigned int> indices_;
    unsigned int vbo_[3];
    unsigned int vao_;
    bool normalized_;

};

#endif
