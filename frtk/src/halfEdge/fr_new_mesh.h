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

class Shape;  //Object container for any 2D or 3D shape
class mesh_halfedge;
class mesh_face;
class mesh_edge;
class mesh_vertex;
class mesh_loop;


class mesh_face {
public:
    mesh_face();
    ~mesh_face();

    unsigned int     ID;  //face ID
    Shape* fshape ;
    std::shared_ptr<mesh_halfedge> hedge ;    //first half edge in the face
    bool       visible;
    bool       selected;
    glm::vec3  normal;
    std::shared_ptr < mesh_face> next;
    std::shared_ptr < mesh_face> prev;
};

class mesh_halfedge {
public:
    mesh_halfedge();
    ~mesh_halfedge();
    std::shared_ptr < mesh_halfedge> twin ; //Reverse half edge
    std::shared_ptr < mesh_vertex> vertex;
    std::shared_ptr < mesh_face> face ;

    std::shared_ptr < mesh_halfedge> next ;
    std::shared_ptr < mesh_halfedge> prev;
};

class mesh_vertex {
public:
    mesh_vertex();
    ~mesh_vertex();
    std::shared_ptr<mesh_halfedge> vedge ;
    glm::vec3 vertexValue;
    bool      visible ;
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
    std::vector<std::shared_ptr<mesh_face>> FaceObjects; //Hold all faces for the shape and all other elements

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

    size_t nVertexes, nTriangles, nQuads;

    unsigned int vbo_[3];
    unsigned int vao_;
    bool normalized_;

private:
    Fr_GL3Window* linktoMainWindow;
};

#endif
