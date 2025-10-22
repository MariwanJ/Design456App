#ifndef FR_NAVICUBE_MESH_H
#define FR_NAVICUBE_MESH_H
#include <frtk.h>

// Cube mesh in OFF format
//Core box	1 pcs



static const std::string cubeCoreOff = R"OFF(OFF
8 12 0
0 0 2
0 0 8
0 6 2
0 6 8
6 0 8
6 0 2
6 6 2
6 6 8
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 4 0
3 0 4 1
3 7 6 2
3 7 2 3
3 2 6 0
3 0 6 5
3 7 3 1
3 7 1 4
)OFF";
//------------------------------------------------------------------------------------------------------------
/*        6 boxes represent top,bottom, right, left, front ,back*/
// Botom box 
static const std::string naviCubeBottom= R"OFF(OFF
8 12 0
0 0 2
0 6 2
0 0 0
0 6 0
6 6 2
6 6 0
6 0 2
6 0 0
3 0 1 2
3 2 1 3
3 1 4 3
3 3 4 5
3 4 6 7
3 4 7 5
3 6 0 2
3 6 2 7
3 4 1 0
3 4 0 6
3 3 5 2
3 2 5 7
)OFF";

//Top box
static const std::string naviCubeTop = R"OFF(OFF
8 12 0
0 6 8
0 0 8
0 0 10
0 6 10
6 6 8
6 6 10
6 0 8
6 0 10
3 0 1 2
3 0 2 3
3 4 0 3
3 4 3 5
3 6 4 7
3 7 4 5
3 1 6 2
3 2 6 7
3 0 4 1
3 1 4 6
3 5 3 2
3 5 2 7
)OFF";

//left box
static const std::string naviCubeLeft = R"OFF(OFF
8 12 0
0 0 2
6 0 2
0 -2 2
6 -2 2
6 0 8
6 -2 8
0 0 8
0 -2 8
3 0 1 2
3 2 1 3
3 1 4 3
3 3 4 5
3 4 6 7
3 4 7 5
3 6 0 2
3 6 2 7
3 4 1 0
3 4 0 6
3 3 5 2
3 2 5 7
)OFF";
//Right box
static const std::string naviCubeRight = R"OFF(OFF
8 12 0
6 6 2
0 6 2
0 8 2
6 8 2
6 6 8
6 8 8
0 6 8
0 8 8
3 0 1 2
3 0 2 3
3 4 0 3
3 4 3 5
3 6 4 7
3 7 4 5
3 1 6 2
3 2 6 7
3 0 4 1
3 1 4 6
3 5 3 2
3 5 2 7
)OFF";

//Front Box
static const std::string naviCubeFront = R"OFF(OFF
8 12 0
6 0 8
6 0 2
8 0 2
8 0 8
6 6 8
8 6 8
6 6 2
8 6 2
3 0 1 2
3 0 2 3
3 4 0 3
3 4 3 5
3 6 4 7
3 7 4 5
3 1 6 2
3 2 6 7
3 1 0 6
3 6 0 4
3 3 2 7
3 3 7 5
)OFF";

//Back Box 
static const std::string naviCubeBack = R"OFF(OFF
8 12 0
6 0 8
6 0 2
8 0 2
8 0 8
6 6 8
8 6 8
6 6 2
8 6 2
3 0 1 2
3 0 2 3
3 4 0 3
3 4 3 5
3 6 4 7
3 7 4 5
3 1 6 2
3 2 6 7
3 1 0 6
3 6 0 4
3 3 2 7
3 3 7 5
)OFF";
//---------------------------ON THE BOTTOM---------------------------------------------------------

/*       The bar boxes now          4pcs on the bottom   */
static const std::string naviCubeBottomFront = R"OFF(OFF
8 12 0
6 6 0
6 6 2
8 6 2
8 6 0
6 0 2
6 0 0
8 0 2
8 0 0
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 6
3 1 6 2
3 5 0 7
3 7 0 3
3 4 1 5
3 5 1 0
3 2 6 7
3 2 7 3
)OFF";

static const std::string naviCubeBottomLeft = R"OFF(OFF
8 12 0
6 0 2
6 -2 2
6 0 0
6 -2 0
0 -2 2
0 0 2
0 0 0
0 -2 0
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 6
3 6 0 2
3 1 4 7
3 1 7 3
3 0 5 4
3 0 4 1
3 6 2 7
3 7 2 3
)OFF";


static const std::string naviCubeBottomRight = R"OFF(OFF
8 12 0
6 6 2
6 6 0
6 8 2
6 8 0
0 6 0
0 6 2
0 8 2
0 8 0
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 6
3 6 0 2
3 1 4 7
3 1 7 3
3 0 5 4
3 0 4 1
3 6 2 7
3 7 2 3
)OFF";

static const std::string naviCubeBottomBack = R"OFF(OFF
8 12 0
-2 6 2
0 6 2
0 6 0
-2 6 0
0 0 2
-2 0 2
0 0 0
-2 0 0
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 6
3 1 6 2
3 5 0 7
3 7 0 3
3 4 1 5
3 5 1 0
3 2 6 7
3 2 7 3
)OFF";
//---------------------------------FRONT VIEW ----------------------------------------------------------------------------
/*                  Middle bars 4 pcs */

static const std::string naviCubeFrontRight = R"OFF(OFF
8 12 0
6 8 8
6 6 8
8 6 8
8 8 8
6 6 2
6 8 2
8 6 2
8 8 2
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 6
3 1 6 2
3 5 0 7
3 7 0 3
3 4 1 5
3 5 1 0
3 2 6 7
3 2 7 3
)OFF";

/*                  Middle bars front  */

static const std::string naviCubeFrontLeft = R"OFF(OFF
8 12 0
0 6 8
-2 6 8
0 6 10
-2 6 10
-2 0 8
0 0 8
0 0 10
-2 0 10
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 6
3 6 0 2
3 1 4 7
3 1 7 3
3 0 5 4
3 0 4 1
3 6 2 7
3 7 2 3
)OFF";

//-------------------------------------BACK VIEW------------------------------------------------------------------------------

// after rotating the view to back :  side bars
static const std::string naviCubeBackRight = R"OFF(OFF
8 12 0
0 -2 8
0 0 8
-2 0 8
-2 -2 8
0 0 2
0 -2 2
-2 0 2
-2 -2 2
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 6
3 1 6 2
3 5 0 7
3 7 0 3
3 4 1 5
3 5 1 0
3 2 6 7
3 2 7 3
)OFF";


static const std::string naviCubeBackLeft = R"OFF(OFF
8 12 0
-2 6 8
0 6 8
0 8 8
-2 8 8
0 6 2
-2 6 2
0 8 2
-2 8 2
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 6
3 1 6 2
3 5 0 7
3 7 0 3
3 4 1 5
3 5 1 0
3 2 6 7
3 2 7 3
)OFF";


static const std::string naviCubeBackTop = R"OFF(OFF
8 12 0
0 6 8
-2 6 8
0 6 10
-2 6 10
-2 0 8
0 0 8
0 0 10
-2 0 10
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 6
3 6 0 2
3 1 4 7
3 1 7 3
3 0 5 4
3 0 4 1
3 6 2 7
3 7 2 3
)OFF";

static const std::string naviCubeBackBottom = R"OFF(OFF
8 12 0
-2 6 2
0 6 2
0 6 0
-2 6 0
0 0 2
-2 0 2
0 0 0
-2 0 0
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 6
3 1 6 2
3 5 0 7
3 7 0 3
3 4 1 5
3 5 1 0
3 2 6 7
3 2 7 3
)OFF";



//-------------------------------------FRONT VIEW----------------------------------------------
/*  Here we define the small cubes on the cornvers*/

static const std::string naviCubeFrontBottomRight = R"OFF(OFF
8 12 0
6 8 2
6 6 2
8 6 2
8 8 2
6 6 0
6 8 0
8 6 0
8 8 0
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 2
3 2 4 6
3 5 0 3
3 5 3 7
3 4 1 0
3 4 0 5
3 2 6 3
3 3 6 7
)OFF";

static const std::string naviCubeFrontBottomLeft = R"OFF(OFF
8 12 0
6 0 0
6 0 2
8 0 2
8 0 0
6 -2 2
6 -2 0
8 -2 2
8 -2 0
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 2
3 2 4 6
3 5 0 3
3 5 3 7
3 4 1 0
3 4 0 5
3 2 6 3
3 3 6 7
)OFF";

static const std::string naviCubeFrontTopLeft = R"OFF(OFF
8 12 0
6 0 8
6 0 10
8 0 8
8 0 10
6 -2 10
6 -2 8
8 -2 8
8 -2 10
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 2
3 5 2 6
3 1 4 3
3 3 4 7
3 0 5 1
3 1 5 4
3 6 2 3
3 6 3 7
)OFF";

static const std::string naviCubeFrontTopRight = R"OFF(OFF
8 12 0
6 6 10
6 6 8
8 6 8
8 6 10
6 8 8
6 8 10
8 8 8
8 8 10
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 2
3 2 4 6
3 5 0 3
3 5 3 7
3 4 1 0
3 4 0 5
3 2 6 3
3 3 6 7
)OFF";

//--------------------------------BACK VIEW ----------------------------------------------------
// small cubes after rotating the view to back 

static const std::string naviCubeBackTopRight = R"OFF(OFF
8 12 0
0 6 8
0 8 8
0 6 10
0 8 10
-2 8 8
-2 6 8
-2 6 10
-2 8 10
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 2
3 5 2 6
3 1 4 3
3 3 4 7
3 0 5 1
3 1 5 4
3 6 2 3
3 6 3 7
)OFF";

static const std::string naviCubeBackTopLeft = R"OFF(OFF
8 12 0
0 0 10
0 0 8
-2 0 8
-2 0 10
0 -2 8
0 -2 10
-2 -2 8
-2 -2 10
3 0 1 2
3 0 2 3
3 4 5 6
3 6 5 7
3 1 4 2
3 2 4 6
3 5 0 3
3 5 3 7
3 4 1 0
3 4 0 5
3 2 6 3
3 3 6 7
)OFF";

static const std::string naviCubeBackBottomRight = R"OFF(OFF
8 12 0
0 6 2
0 6 0
0 8 2
0 8 0
-2 6 0
-2 6 2
-2 8 2
-2 8 0
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 2
3 5 2 6
3 1 4 3
3 3 4 7
3 0 5 1
3 1 5 4
3 6 2 3
3 6 3 7
)OFF";

static const std::string naviCubeBackBottomLeft = R"OFF(OFF
8 12 0
0 0 2
0 0 0
-2 0 2
-2 0 0
0 -2 0
0 -2 2
-2 -2 2
-2 -2 0
3 0 1 2
3 2 1 3
3 4 5 6
3 4 6 7
3 5 0 2
3 5 2 6
3 1 4 3
3 3 4 7
3 0 5 1
3 1 5 4
3 6 2 3
3 6 3 7
)OFF";

/*                  Middle bars left*/


std::vector<const std::string*> meshDataPointers = {
     &cubeCoreOff, &naviCubeBottom, &naviCubeTop, &naviCubeLeft,
     &naviCubeRight, &naviCubeFront, &naviCubeBack,
     &naviCubeBottomFront, &naviCubeBottomLeft, &naviCubeBottomRight,
     &naviCubeBottomBack, &naviCubeFrontRight, &naviCubeFrontLeft,
     &naviCubeBackRight, &naviCubeBackLeft, &naviCubeBackTop,
     &naviCubeBackBottom, &naviCubeFrontBottomRight, &naviCubeFrontBottomLeft,
     &naviCubeFrontTopLeft, &naviCubeFrontTopRight, &naviCubeBackTopRight,
     &naviCubeBackTopLeft, &naviCubeBackBottomRight, &naviCubeBackBottomLeft
};

#endif //FR_NAVICUBE_MESH_H