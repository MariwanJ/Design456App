#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <stdio.h>
#include <stdlib.h>

/*
from MESH.H
*/

#define  VERTEX    101
#define  HALFEDGE  102
#define  EDGE      103
#define  LOOP      104
#define  FACE      105
#define  SOLID     106

#define  NIL 0
#define  TRUE 1
#define  FALSE 0

#define SWAP(t,x,y)     { t = x; x = y; y = t; }

#define NEW(p,type)     if ((p=(type *) malloc (sizeof(type))) == NIL) {\
                                printf ("Out of Memory!\n");\
                                exit(0);\
                        }

#define FREE(p)         if (p) { free ((char *) p); p = NIL; }

#define ADD( head, p )  if ( head )  { \
                                p->prev = head->prev; \
                                p->next = head; \
                                head->prev = p; \
                                p->prev->next = p; \
                        } \
                        else { \
                                head = p; \
                                head->next = head->prev = p; \
                        }

#define DELETE( head, p )   if ( head )  { \
                                if ( head == head->next ) \
                                        head = NIL;  \
                                else if ( p == head ) \
                                        head = head->next; \
                                p->next->prev = p->prev;  \
                                p->prev->next = p->next;  \
                                FREE( p ); \
                        }

typedef int                  Id;
typedef struct solid      Solid;
typedef struct face       Face;
typedef struct loop       Loop;
typedef struct halfedge   HalfEdge;
typedef struct vertex     Vertex;
typedef struct edge       Edge;
typedef struct node       Node;

struct node {
    int    type;
    void* p;
    double v;

    Node* next;
    Node* prev;
};

struct solid {
    Face* sfaces;
    Edge* sedges;
    Vertex* sverts;
    double   center[3];
};

struct face {
    Id          faceno;

    Loop* floop;
    Solid* fsolid;
    double      normal[3];

    Face* next;
    Face* prev;

    int       alivef;
};

struct edge {
    HalfEdge* he1;
    HalfEdge* he2;
    Solid* esolid;

    Edge* next;
    Edge* prev;

    int      alive;
};

struct halfedge {
    Edge* hedge;
    Loop* hloop;
    Vertex* hvert;

    HalfEdge* next;
    HalfEdge* prev;

    int     aliveh; //TODO: Check if we need this???
};

struct vertex {
    Id        vertexno;
    HalfEdge* vedge;
    double    gauss_cur;
    double    vcoord[3];
    double    ncoord[3];

    Vertex* next;
    Vertex* prev;

    int      alivev; //TODO: Check if we need this???
};

struct loop {
    HalfEdge* ledges;
    Face* lface;

    int      alivel;  //TODO: Check if we need this???
};



/*****************************************************************************************************/
/*
    FROM FUNCS.H
*/

/*ar rvf libmesh.a edge.o face.o edgelist.o facelist.o halfedge.o loop.o solid.o vertex.o vertexlist.o
ranlib libmesh.a
*/

void  VertexIDReset();
void VertexConstruct(Solid**, double, double, double);
void VertexDestruct(Vertex**);
HalfEdge* VertexFirstOutHalfEdge(Vertex*);
HalfEdge* VertexNextOutHalfEdge(HalfEdge*);
HalfEdge* VertexFirstInHalfEdge(Vertex*);
HalfEdge* VertexNextInHalfEdge(HalfEdge*);
HalfEdge* HalfEdgeMate(HalfEdge*);
Face* VertexFirstFace(Vertex* v);
Face* VertexNextFace(Vertex* v, Face* f);
int     VertexCheckNeighorConvexity(Vertex*);
Vertex* VertexFirstVertex(Vertex*);
Vertex* VertexNextVertex(Vertex*, Vertex*);
void VertexConstructN(Solid**, double, double, double, double, double, double);
void VertexCheckConsistency(Vertex*);

/*----------------------------------------------------------------------

  for checking manifold structure

---------------------------------------------------------------------*/
int VertexFaceNumber(Vertex*);

void HalfEdgeConstruct(Loop**, Vertex*);
void HalfEdgeDestruct(HalfEdge**);
HalfEdge* HalfEdgeMate(HalfEdge*);
Vertex* HalfEdgeStartVertex(HalfEdge*);
Vertex* HalfEdgeEndVertex(HalfEdge*);
int      HalfEdgeMerge(HalfEdge*);
void     HalfEdgeExtend(HalfEdge*);
double   HalfEdgeCost(HalfEdge*, double (*)(Face*));
Vertex* HalfEdgeEndVertex(HalfEdge*);
Vertex* HalfEdgeStartVertex(HalfEdge*);
/*---------------------------------------------------------------------

  checking if current halfedge is mergable

----------------------------------------------------------------------*/
int   HalfEdgeMergable(HalfEdge*);

void EdgeConstruct(Solid**, HalfEdge*, HalfEdge*);
void EdgeDestruct(Edge**);
Face* EdgeFirstFace(Edge*);
Face* EdgeSecondFace(Edge*);

void FaceConstruct(Solid**, Vertex*, Vertex*, Vertex*);
void FaceDestruct(Face**);
int FaceOrientation(Face*, double, double, double);
int FaceOrientation2(Face*, double, double, double, double);
void FacePrint(Face*);
void FaceNormal(Face*);

void LoopConstruct(Face**, Vertex*, Vertex*, Vertex*);
void LoopDestruct(Loop**);

void    VertexListConstruct(Solid**, int, FILE*);
void    VertexListDestruct(Solid**);
Vertex* VertexListIndex(Solid*, int);
void  VertexListConstructNoff(Solid**, int, FILE*);

void  EdgeListConstruct(Solid**);
void  EdgeListDestruct(Solid**);

void  FaceListConstruct(Solid**, int, FILE*);
void  FaceListDestruct(Solid**);
void  FaceListOutput(Face*);

void SolidConstruct(Solid**, char*);
void SolidCenter(Solid* s);
void SolidDestruct(Solid**);
int  SolidConvexity(Solid* s);
void SolidConstructNoff(Solid**, char*);

int  ListInsertNode(Node**, void*, int);
int  ListDeleteNode(Node**, void*, int);
void ListDestruct(Node**);

void downheap(int);
void upheap(int);
Node* Remove();
void heapsort(Node**, int);
int  heapIndex(Node* v);
void heapConstruct(Node**, int);
void heapPrint();
Node* heapSelectMin();
Node* heapNode(void*);
void  heapUpheap(void*);
void  heapDownheap(void*);
void  heapCheck();
int   heapEmpty();
double  Volumed(Face* f, double x, double y, double z);

#endif