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
#include <frtk.h>
#include <Fr_Core.h>
#include <fr_transform.h>

/**
 * 
 * 
 *          Note: Some of these varialbe are declared with wrong type. I just wanted to have them here. 
 *                  Durign a better understaning of the Wing3D, these will be corrected. 
 *                  At the momnet I want to understan the code. It is not easy to understand erlang.
 * .
 */
struct vtx;
struct edge;
struct face;
struct body;
struct we;
struct camera;
struct shape;

// The Winged-Edge data structure.
// See http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/model/winged-e.html


typedef enum stateEnum {
    undo = 0,
    redo = 1,
};

typedef enum selMODE {
    vertex = 0,
    edge = 1,
    face = 2,
    body = 3
};

// Edge in a winged-edge shape.
class Vert {
    float x, y, z;
    std::shared_ptr<EDGE> edge;
};
struct EDGE {
    std::shared_ptr<Vert> v1;					            //Edges verticies
    std::shared_ptr<Vert> v2;
    std::shared_ptr<struct face> 	   leftFace;				//Left face
    std::shared_ptr<struct face> 	   rigthFace;				//Right face
    std::shared_ptr<EDGE>    leftEdgCW;					    //Left traversal predecessor
    std::shared_ptr<EDGE> 	 leftEdgCCW;					    //Left traversal successor
    std::shared_ptr<EDGE>    rightEdgCW;					    //Left traversal predecessor
    std::shared_ptr<EDGE> 	 rightEdgCCW;					    //Left traversal successor

};
// A face in a winged-edge shape.
struct face {
    std::shared_ptr<struct edge> 	 edge_;					//Incident edge
};

class we {
public:
    void build ()
    void build(std::shared_ptr<face> FS, std::shared_ptr<Vertex> VS);
    void build(unsigned inte identity,std::shared_ptr<face> FS, std::shared_ptr<Vertex> VS, std::shared_ptr<edge>He);
    void build(glm::mat4 Matrix, std::shared_ptr<face> FS, std::shared_ptr<Vertex>  VS, std::shared_ptr<edge>He);
    void build(std::shared_ptr<face> FS, std::shared_ptr<Vertex> VS, std::shared_ptr<edge>He);

    void build_edges_only(std::shared_ptr<face> Faces);
    void build_rest(std::shared_ptr<face> FS, std::shared_ptr<Vertex> VS, std::shared_ptr<edge>He);

public: 
    std::vector<std::shared_ptr<struct edge>> 	 es;			//gb_tree containing edges
    std::vector<std::shared_ptr<glm::vec3>> 	 vs;		    //gb_tree containing vertices
    std::vector<std::shared_ptr<struct face>> 	 fs;			//gb_tree containing faces
    std::vector < std::shared_ptr<struct edge>> he;				//gb_sets containing hard edges

    unsigned int  first_id;				                        //First ID used
    unsigned int next_id;				                        //Next free ID for vertices; edges; and faces


};


