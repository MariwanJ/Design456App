#ifndef WINGS_H
#define WINGS_H

#include <../SDL2-2.24.2/include/SDL.h>
#include <../SDL2-2.24.2/include/SDL_main.h>

#incldue <sdl_events.h>
#incldue <sdl_events.h>
#incldue <sdl_video.h>
#incldue <sdl_keyboard.h>

//OpenGL
#include<Gl/gl.h>
#include<Gl/glu.h>

#define WINGS_VERSION 0.8
#define CHAR_HEIGHT 14
#define CHAR_WIDTH 7
#define CHAR_HEIGHT 14
#define CHAR_WIDTH 7
#define LINE_HEIGHT CHAR_HEIGHT+3
#define GROUND_GRID_SIZE 10
#define CAMERA_DIST 8*ROUND_GRID_SIZE

#define UNDO_LEVELS 32
#define HIT_BUF_SIZE  2048

struct opt {
    bool wire=false;      //Wireframe model (true/false).    
    bool ground=true;     //Show ground plane (true/false). 
    bool axes=true;       //Show axes. 
    bool ortho=false;     //Orthogonal view.   
    bool smooth = false;        //Smooth preview.
};

struct dl {
    void* 	 we = nullptr;				        //Winged edge objects.
    void* 	 dragging = nullptr;				//WE faces being dragged.
    void* 	 drag_faces = nullptr;			//GbSet containing faces.
    void* 	 pick = nullptr;				//For picking.
};
enum selctionmode {
vertex = 0;
edge = 1;
face = 2;
body = 3;
};
struct st {
    auto 	 shapes;				//All visible shapes
    auto 	 hidden;				//Hidden shapes
    selctionmode  	 selmode;				//Selection mode: vertex; edge, face, body
    auto 	 sel;					//Current sel: [ Id,GbSet ]
    auto 	 hsel;					//Hidden sel: GbSet
    auto 	 ssel;					//Saved selection.
    auto 	 mat;					//Defined materials GbTree).
    int 	 next_tx = 100;				//Next OpenGL texture ID.
    auto 	 drag;					//Current drag information or  'undefined' if no drag  in progress.
    auto 	 camera;				//Camera information or  'undefined'.
    void* 	 dl = none;				//Cached display lists.
    auto 	 opts;					//Options record.
    std::string 	 file;					//Current filename.
    bool 	 saved;					//True if model has been saved.
    int 	 onext;					//Next object id to use.
    auto 	 hit_buf;				//Hit buffer for hit testing.
    float 	 inf_r;					//Radius of influence for magnet).
    std::string 	 last_command;				//Last command.
    void 	 *bb = nullptr;				//Saved bounding box.
    
     	 //// The current view.
    int 	 origo;
    float 	 distance;				// From origo
    auto 	 azimuth;
    auto 	 elevation;
    float    pan_x;					//Panning in X direction.
    float 	 pan_y					//Panning in Y direction
};
// Shape (or object) which can be implemented in different ways.

struct shape {
    int 	 id;					//Shape id
    std::string 	 name;					//Shape name
    glm::mat4 	 matrix = e3d_mat:identity);		//Transformation matrix
    void* sh;					//The shape itself:n 'we' or 'trimesh'
};

// The Winged-Edge data structure.
// See http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/model/winged-e.html

struct we {
    auto 	 es;					//gb_tree containing edges
    auto 	 vs;					//gb_tree containing vertices
    auto 	 fs;					//gb_tree containing faces
    auto 	 he;					//gb_sets containing hard edges
    int 	 first_id;				//First ID used
    auto 	 next_id;				//Next free ID for vertices;
                                    // edges; and faces
};

// Edge in a winged-edge shape.
struct edge {
    auto 	 vs;					//Start vertex for edge
    auto 	 ve;					//End vertex for edge
    auto 	 lf;					//Left face
    auto 	 rf;					//Right face
    auto 	 ltpr;					//Left traversal predecessor
    auto 	 ltsu;					//Left traversal successor
    auto 	 rtpr;					//Right traversal predecessor
    auto 	 rtsu					//Right traversal successor
};
// A face in a winged-edge shape.

struct face {
    auto 	 edge;					//Incident edge
    auto 	 mat = default				//Material for face
};
// A vertex in a winged-edge shape.

struct vtx {
    auto 	 edge;					//Incident edge
    auto 	 pos					//Position  X;Y,Z )
};






#endif // !WINGS_H
