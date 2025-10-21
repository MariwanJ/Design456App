#ifndef FR_NAVICUBE_MESH_H
#define FR_NAVICUBE_MESH_H
#include <frtk.h>

// Cube mesh in OFF format
static const std::string cubeCoreOff = R"OFF(
OFF
 12 0
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




#endif //FR_NAVICUBE_MESH_H