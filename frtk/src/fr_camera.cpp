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

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <fr_camera.h>
#include <fr_manipulator.h>
/**
 normal
     (0.707107, -0.408248, 0.57735, 0),
    (0.707107, 0.408248, -0.57735, 0),
    (-3.41002e-07, 0.816497, 0.57735, 0),
    (0, 0, 0, 1))

top
Matrix (1,0,0,0),
        (0,1,0,0),
        (0,0,1,0),
        (0,0,0,1)

bottom
    (1,0,0,0),
    (0,-1,8.74228e-08,0),
    (0,-8.74228e-08,-1,0),
    (0,0,0,1)

front
    (1,1.26441e-07,4.21468e-08,0),
    (4.21468e-08,2.44249e-15,-1,0),
    (-1.26441e-07,1,-2.88658e-15,0),
    (0,0,0,1)

Rear
    (-1, -2.95028e-07, 2.52881e-07, 0), 
    (2.52881e-07, 1.68587e-07, 1, 0), 
    (-2.95028e-07, 1, -1.68587e-07, 0), 
    (0, 0, 0, 1)

left 
    (0,0,-1,0),
    (-1,0,0,0),
    (0,1,0,0),
    (0,0,0,1)

 right
    (-2.38419e-07,1.19209e-07,1,0),
    (1,-2.38419e-07,2.38419e-07,0),
    (2.38419e-07,1,-1.19209e-07,0),
    (0,0,0,1)






*/

Camera::Camera() :
    camPosition_{ 0, 0, 3 },
    direction_{ 0, 0, 0 },
    up_{ 0, 1, 0 },
    fovy_{ 45 },
    znear_{ 0.1f },
    zfar_{ 150.0f },
    aspectRatio_{ 1.778f },
    manipulator_{},
    //projectionMatrix_(glm::ortho(-800, 800, -600, 600, -1000, 1000)),

    projectionMatrix_(glm::perspective(glm::radians(fovy_), aspectRatio_, znear_, zfar_)),
    camType_(CameraList::PERSPECTIVE){
    type(NODETYPE::FR_CAMERA);

}

void Camera::SetCamPosition(float x, float y, float z) {
    camPosition_ = glm::vec3(x, y, z);
}

bool  Camera::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
{
    if (!active_)
        return false;

    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    switch ((int)camType_) {
    case (int)CameraList::PERSPECTIVE: {
        //RIGHT           LEFT   BOTTOM    TOP
        projection = glm::perspective(glm::radians(fovy_), aspectRatio_, znear_, zfar_);
    } break;
    case (int)CameraList::ORTHOGRAPHIC: {
        projection = glm::ortho(camPosition_.x - 30, camPosition_.x + 30, camPosition_.y - 30, camPosition_.y + 30, znear_, zfar_);
    }break;
    
    }
        modelview = glm::lookAt(camPosition_, direction_, up_);
    if (manipulator_)
        modelview *= manipulator_->GetMatrix(glm::normalize(direction_  -camPosition_));
    return true;
}

void Camera::SetCenter(float x, float y, float z) {
    direction_ = glm::vec3(x, y, z);
}

void Camera::SetUp(float x, float y, float z) {
    up_ = glm::vec3(x, y, z);
}

void Camera::SetPerspective(float fovy, float znear, float zfar) {
    fovy_ = fovy;   //LEFT
    znear_ = znear;  //BOTTOM
    zfar_ = zfar;    //TOP
}
/**
 * Get camera configurations and saved in data.
 * 
 * \param data ref variable keeps the configuration
 */
void Camera::getUserData(userData_& data)
{
    data.aspectRatio_ = aspectRatio_;
    data.camPosition_ = camPosition_;
    data.camType_ = camType_;
    data.direction_ = direction_;
    data.fovy_ = fovy_;
    data.up_ = up_;
    data.zfar_ = zfar_;
    data.znear_ = znear_;
}

void Camera::setUserData(userData_& data)
{
    aspectRatio_  =data.aspectRatio_   ; 
    camPosition_  =data.camPosition_   ; 
    camType_      =data.camType_       ; 
    direction_    =data.direction_        ; 
    fovy_         =data.fovy_          ; 
    up_           =data.up_            ; 
    zfar_         =data.zfar_          ; 
    znear_        =data.znear_         ; 
}

void Camera::SetManipulator(std::shared_ptr<Manipulator> manipulator) {
    manipulator_ = std::move(manipulator); //Move ownership to this class
}

std::shared_ptr<Manipulator> Camera::getManipulator()
{
    return manipulator_;
}
/**
 * 
 * Home values.
 * 
 */
void Camera::setupCameraHomeValues(){
    if (!active_)
        return; //do nothing
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    aspectRatio_ = (float)vp[2] / vp[3];

    switch (camType_) {
    case CameraList::PERSPECTIVE: {
        SetCamPosition(-10, 0, -30);
        SetCenter(0, 0, 100);
        SetUp(0, 1, 0);
        } break;
    case CameraList::ORTHOGRAPHIC: {
        //TODO FIXME
        SetCamPosition(-6, 2, -20);
        SetCenter(0, 0, 100);
        SetUp(0, 1, 0);
        } break;
    case CameraList::TOP: {
        SetCamPosition(0, 2, -20);
        SetCenter(0, 0, 0);
        SetUp(0, 1, 0);
        } break;
    case CameraList::BOTTOM: {
        SetCamPosition(10, 2, -20);
        SetCenter(0, 0, 0);
        SetUp(1, 0, 0);
    } break;

    }
}
/**
*   Set camera type
*/
void Camera::setType(CameraList camTyp)
{
    camType_ = camTyp;
}
/**
 * 
 * Set camera type which affects the setup function.
 * \return 
 */
CameraList  Camera::getType() const
{
    return camType_ ;
}

/**
*   Get Camera Type
*/
CameraList Camera::getCameraType() {
    return camType_;
}

glm::mat4 Camera::getPorjection()
{
    return glm::mat4();
}
