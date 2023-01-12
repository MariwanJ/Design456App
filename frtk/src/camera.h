#ifndef CAMERA_H
#define CAMERA_H

#include <Fr_Core.h>

enum camType {
    notDefined = 0,
    Orthographic,
    Perspective
};

class Camera
{
public:
    Camera();
    ~Camera();
    void setCameraType(camType t);
private:
    camType  _camType;
};

#endif