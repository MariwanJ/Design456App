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

#ifndef FR_MESH_H
#define FR_MESH_H

#include<frtk.h>
#include<fr_core.h>
#include <glm/glm.hpp>
#include<fr_transform.h>
#include<halfEdge/fr_genID.h>

#define  CHAR_HEIGHT  14
#define  CHAR_WIDTH  7
#define  LINE_HEIGHT  CHAR_HEIGHT+3
#define  GROUND_GRID_SIZE  10
#define  CAMERA_DIST  8*GROUND_GRID_SIZE
#define  MOUSE_DIVIDER  500
#define  UNDO_LEVELS  32
#define  HIT_BUF_SIZE  2048

//class Transform;
struct vtx;
struct edge;
struct face;
struct body;
struct we;
struct drag;
struct camera;
struct shape;
//
//typedef enum stateEnum {
//    undo = 0,
//    redo = 1,
//};

//struct undo {
//    int max;					//Max levels of undo.
//    int 	 levels;				//Current number of levels.
//    unsigned int 	 top;					//Top of stack.
//    unsigned int 	 bottom;				//Bottom of stack.
//    stateEnum 	 next_is_undo;				//State of undo/redo toggle.
//    stateEnum 	 undone;				//States that were undone.
//};

typedef enum selMODE {
    vertex = 0,
    edge = 1,
    face = 2,
    body = 3
};

struct shape {
    unsigned int 	 id;				//Shape id
    std::string  name;					//Shape name
    glm::mat4 matrix;                   // = e3d_mat:identity;		//Transformation matrix
    std::shared_ptr<we> 	 sh;		//The shape itself:              // record
};

// The essential part of the state record.
struct est {
    struct shape shapes;
    selMODE 	 selmode;
    std::string 	 sel;
};

//typedef struct opt {
//    bool wire = false;				//Wireframe model true/false).
//    bool ground = true;				//Show ground plane true/false).
//    bool axes = true;				//Show axes.
//    bool ortho = false;				//Orthogonal view.
//    bool smooth = false;			//Smooth preview.
//};

// Edge in a winged-edge shape.

struct edge {
    unsigned int id;        //Edge ID
    glm::vec3 	 vs;					//Start vertex for edge
    glm::vec3 	 ve;					//End vertex for edge
    std::shared_ptr<struct face> 	   lf;					//Left face
    std::shared_ptr<struct face> 	   rf;					//Right face
    std::shared_ptr<edge>    ltpr;					//Left traversal predecessor
    std::shared_ptr<edge> 	 ltsu;					//Left traversal successor
    std::shared_ptr<edge> 	 rtpr;					//Right traversal predecessor
    std::shared_ptr<edge> 	 rtsu;				//Right traversal successor
};
// A face in a winged-edge shape.

struct face {
    unsigned int id;
    std::vector<std::shared_ptr<struct edge>> edge_;					//Incident edge
    std::vector<std::shared_ptr<Material>> 	 mat;// = default				//Material for face
};
// A vertex in a winged-edge shape.

typedef struct vtx {
    std::shared_ptr<struct edge> 	 edge_;					//Incident edge
    glm::vec3 pos;					//Position  X;Y,Z )
};

typedef union OBJTYPE {
    struct vtx vertex_;
    struct edge edge_;
    Transform body_;  //Let us assume that body is a Transform
    struct face face_;
};
typedef struct SSEL {
    selMODE mode;
    std::vector <OBJTYPE> ssel;
};

typedef struct WE {
    std::vector<std::shared_ptr<struct face>> 	 fs;		//gb_tree containing faces
    std::vector<std::shared_ptr<struct edge>> 	 es;		//gb_tree containing edges
    std::vector<std::shared_ptr<glm::vec3>> 	 vs;	    //gb_tree containing vertices
    std::vector < std::shared_ptr<struct edge>>  he;		//gb_sets containing hard edges
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
    unsigned int id;
    std::vector<std::shared_ptr<WE>> wingedObj; //Hold all winged objects in a table that has all elements

private:
    std::vector<float> vertices_;
    std::vector<float> normals_;
    std::vector<unsigned int> indices_;
    unsigned int vbo_[3];
    unsigned int vao_;
    bool normalized_;
};

#endif
