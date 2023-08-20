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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#include <fr_transform.h>
#include <wings3d/fr_genID.h>  //will bring also frtk.h and fr_core.h to here
#include <fr_mesh.h>



#define  CHAR_HEIGHT  14
#define  CHAR_WIDTH  7
#define  LINE_HEIGHT  CHAR_HEIGHT+3
#define  GROUND_GRID_SIZE  10
#define  CAMERA_DIST  8*GROUND_GRID_SIZE
#define  MOUSE_DIVIDER  500
#define  UNDO_LEVELS  32
#define  HIT_BUF_SIZE  2048

struct vtx;
struct edge;
struct face;
struct body;
struct we;
struct drag;
struct camera;
struct shape;

typedef enum stateEnum {
    undo = 0,
    redo = 1,
};

struct undo {
    int max;					//Max levels of undo.
    int 	 levels;				//Current number of levels.
    unsigned int 	 top;					//Top of stack.
    unsigned int 	 bottom;				//Bottom of stack.
    stateEnum 	 next_is_undo;				//State of undo/redo toggle.
    stateEnum 	 undone;				//States that were undone.
};

typedef enum selMODE {
    vertex = 0,
    edge = 1,
    face = 2,
    body = 3
};

struct shape {
    unsigned int 	 id;					//Shape id
    std::string  name;					//Shape name
    glm::mat4 matrix;     // = e3d_mat:identity;		//Transformation matrix
    std::shared_ptr<we> 	 sh;		//The shape itself:                          // record
};

// The essential part of the state record.
struct est {
    struct shape shapes;
    selMODE 	 selmode;
    std::string 	 sel;
};

typedef struct opt {
    bool wire = false;				//Wireframe model true/false).
    bool ground = true;				//Show ground plane true/false).
    bool axes = true;				//Show axes.
    bool ortho = false;				//Orthogonal view.
    bool smooth = false;			//Smooth preview.
};

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
    std::shared_ptr<struct edge> 	 edge_;					//Incident edge
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
    std::vector<std::shared_ptr<struct face>> 	 fs;					//gb_tree containing faces
    std::vector<std::shared_ptr<struct edge>> 	 es;					//gb_tree containing edges
    std::vector<std::shared_ptr<glm::vec3>> 	 vs;		    //gb_tree containing vertices
    std::vector < std::shared_ptr<struct edge>> he;					//gb_sets containing hard edges
};

class Shape {

public:
    Shape(std::string fn);
    int buildFromMesh();
    int buildFromOff();

public:
    unsigned int id;
    Mesh meshObj;
    std::vector<std::shared_ptr<WE>> wingedObj; //Hold all winged objects in a table that has all elements

};
















































/*default st

   St0 = #st{   shapes=Empty,
                hidden=Empty,
                selmode=face,
                sel=[],
                hsel=Empty,
                ssel={face,[]},
                mat=wings_material:default(),
                saved=true,
                opts=#opt{},
                onext=0,
                last_command=ignore,
                hit_buf=sdl_util:malloc(?HIT_BUF_SIZE, ?GL_UNSIGNED_INT)},
*/






/*
typedef struct dl {
    std::shared_ptr<we> we_ = nullptr;				        //Winged edge objects.
    std::shared_ptr<struct face> dragging = nullptr;				//WE faces being dragged.
    std::vector<std::shared_ptr<struct face>> drag_faces;			//GbSet containing faces.
    void* pick = nullptr;	   //not sure what it should be             //For picking.
};

typedef struct st {
    std::vector<std::shared_ptr<shape>> shapes;				//All visible shapes
    std::vector<std::shared_ptr<Transform>> hidden;				//Hidden shapes
    selMODE  selmode;				//Selection mode:
    // vertex; edge, face, body
    std::vector<std::shared_ptr<Transform>> 	 sel;					//Current sel: [ Id,GbSet ]
    std::vector<std::shared_ptr<Transform>> 	 hsel;					//Hidden sel: GbSet
    SSEL 	 ssel;					//Saved selection.
    std::vector<Material> mat;	     //Defined materials GbTree).
    unsigned int next_tx = 100;		 //Next OpenGL texture ID.
    std::string 	 drag;					//Current drag information or 'undefined' if no drag in progress.
    std::string 	 camera;				//Camera information or'undefined'.
    std::shared_ptr<dl> dl_ = nullptr;				//Cached display lists.
    std::shared_ptr<opt> 	 opts;					//Options record.
    std::string file;					//Current filename.
    bool 	 saved;					//True if model has been saved.
    unsigned int 	 onext;					//Next object id to use.
    std::string 	 hit_buf;				//Hit buffer for hit testing.
    float 	 inf_r;					//Radius of influence for magnet).
    std::string	 last_command;			//Last command.
    std::string 	 bb;				//Saved bounding box.

    //// The current view.
    //auto 	 origo;
    glm::vec3 	 distance;				// From origo
    //auto 	 azimuth;
    //auto 	 elevation;
    unsigned int 	 pan_x;					//Panning in X direction.
    unsigned int 	 pan_y;					//Panning in Y direction
};

*/
// Shape (or object) which can be implemented in different ways.

// The Winged-Edge data structure.
// See http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/model/winged-e.html
