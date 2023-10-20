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
#include <Fr_GL3Window.h>
/*
Normal view - home FreeCAD
,top

position 15.337841 10.960548 102.60384\n
orientation 0 0 1  0\n
nearDistance 102.50124\n
farDistance 102.70644\n
aspectRatio 1\n
focalDistance 100\n
height 44.932899\n\n}\n'

 bottom
 BOTTOM
position 10.531155 7.5401545 -97.396126\n
orientation -0.99999994 1.4210855e-014 9.4830476e-008  3.1415935\n
nearDistance 97.298668\n
farDistance 97.493576\n
aspectRatio 1\n
focalDistance 100\n
height 44.932903\n\n}\n'

front
FRONT
 position 28.817665 -89.039444 2.6038942\n
 orientation -1 4.214686e-007 8.4293717e-008  4.7123895\n
 nearDistance 34.005363\n
 farDistance 144.1835\n
 aspectRatio 1\n
 focalDistance 100\n
 height 44.932899\n\n}\n'

Rear
REAR
position 15.337867 110.96054 2.6038241\n
orientation 1.4901161e-008 -0.70710683 -0.70710671  3.141593\n
nearDistance 55.904575\n
farDistance 166.1265\n
aspectRatio 1\n
focalDistance 100\n
height 44.932899\n\n}\n'

left
 LEFT
 position -71.182274 10.960546 2.6038406\n
 orientation 0.57735014 -0.5773505 -0.5773502  2.0943947\n
 nearDistance 16.166088\n
 farDistance 126.30847\n
 aspectRatio 1\n
 focalDistance 100\n
 height 44.932899\n\n}\n'

 right
RIGHT
 position 115.33784 10.960509 2.6038659\n
 orientation -0.57735032 -0.57735026 -0.5773502  4.1887908\n
 nearDistance 60.277466\n
 farDistance 170.50819\n
 aspectRatio 1\n
 focalDistance 100\n
 height 44.932899\n\n}\n'
*/



Camera::Camera() :
    camPosition_{ 15.f, 11.f, 102.f },
    direction_{ -.098f, -1.372f, 0.0f },
    up_{ -58.84f, 628.451f, 29.412f },
    fovy_{ 102.f},
    znear_{ 0.01},
    zfar_{ 100000},
    aspectRatio_{ 1.2 },
    transform_{},

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

    if (camType_ ==CameraList::ORTHOGRAPHIC) {
        ImVec4 winDim = Fr_GL3Window::getfr_Gl3Window()->getPortViewDimensions();
        float aspect = (float)winDim.z / winDim.w;

       projection = glm::ortho(float(-winDim.z/fovy_), float(winDim.z / fovy_),-winDim.w / fovy_, winDim.w / fovy_, znear_, zfar_);
    }
    else {
        projection = glm::perspective(glm::radians(fovy_), aspectRatio_, znear_, zfar_);
    }
        modelview = glm::lookAt(camPosition_, direction_, up_);
    return true;
}

/**
 * Direct center of the camera.
 *
 * \param x : x axis location
 * \param y : y axis location
 * \param z : z axis location
 */
void Camera::SetCenter(float x, float y, float z) {
    direction_ = glm::vec3(x, y, z);
}

/**
 * Up value of the camera.
 *
 * \param x : x axis location
 * \param y : y axis location
 * \param z : z axis location
 */
void Camera::SetUp(float x, float y, float z) {
    up_ = glm::vec3(x, y, z);
}
/**
 * Set fovy, znear and z far values.
 *
 * \param fovy : Focal of view value
 * \param znear :  Z - Near value
 * \param zfar : z - Far value
 */
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

void Camera::SetTransform(std::shared_ptr<Transform> transform) {
   transform_ = std::move(transform); //Move ownership to this class
}

std::shared_ptr<Transform> Camera::getTransform()
{
    return transform_;
}
/**
 *
 * Home values.
 *
 */



void Camera::setupCameraHomeValues() {
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    auto win = Fr_GL3Window::getfr_Gl3Window();
    if (win == nullptr){
     auto portview = win->getPortViewDimensions();
    aspectRatio_ = float(portview.y / portview.w);
    }
    else{
        aspectRatio_ = (float)vp[2] / vp[3];
    }


        switch (int(camType_)) {
            //TODO: FIXME: If you create more than 6, you should add it here
        case 0: {
            /*Normal view PERSPECTIVE, HOME
                    position 17.463835 -17.463825 13.463827\n
                    orientation 0.74290609 0.30772209 0.59447283  1.2171158\n
                    nearDistance 0.42925534\n
                    farDistance 1761.75\n
                    aspectRatio 1\n
                    focalDistance 30.248238\n
                    heightAngle 0.78539819\n\n}\n'
            */
            SetCamPosition(17.46f, -17.46f, 135.0f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetPerspective(30.248f, 0.429f, 1765.f);
        }break;
        case 1: {
            //ORTHOGRAPHIC

            SetCamPosition(17.46f, -149.46f, 135.46f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetPerspective(30.248f, 0.429f, 1765.f);
        }break;
        case 2: {
            /*TOP
             position 15.337841 10.960548 102.60384\n
             orientation 0 0 1  0\n
             nearDistance 102.50124\n
             farDistance 102.70644\n
             aspectRatio 1\n
             focalDistance 100\n
             height 44.932899\n\n}\n'
            */
            SetCamPosition(-74.f, -74.f, -718.6f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetUp(0.8f, 10.f, 10.f);
            SetPerspective(6.8f, -102.5f, 102.7f);
        }break;
        case 3: {
            /*Bottom
             position 10.531155 7.5401545 -97.396126\n
             orientation -0.99999994 1.4210855e-014 9.4830476e-008  3.1415935\n
             nearDistance 97.298668\n
             farDistance 97.493576\n
             aspectRatio 1\n
             focalDistance 100\n
             height 44.932903\n\n}\n'
            */
            SetCamPosition(10.53f, 7.5f, -97.4f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetPerspective(65, 66.0f, 230.0f);
        }break;
        case 4: {
            /**
             *  FRONT
              position 28.817665 -89.039444 2.6038942\n
              orientation -1 4.214686e-007 8.4293717e-008  4.7123895\n
              nearDistance 34.005363\n
              farDistance 144.1835\n
              aspectRatio 1\n
              focalDistance 100\n
              height 44.932899\n\n}\n'
                     *
             */
            SetCamPosition(28.8f, -89.0f, 2.6f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetPerspective(100.0f, 34.0f, 144.18f);
        }break;
        case 5: {
            /*REAR
                position 15.337867 110.96054 2.6038241\n
                orientation 1.4901161e-008 - 0.70710683 - 0.70710671  3.141593\n
                nearDistance 55.904575\n
                farDistance 166.1265\n
                aspectRatio 1\n
                focalDistance 100\n
                height 44.932899\n\n}\n'
                */
            SetCamPosition(15.33f, 110.9f, 2.6f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetPerspective(100.0f, 55.9f, 166.12f);
        }break;
        case 6: {
            /*
            RIGHT
                position 115.33784 10.960509 2.6038659\n
                orientation - 0.57735032 - 0.57735026 - 0.5773502  4.1887908\n
                nearDistance 60.277466\n
                farDistance 170.50819\n
                aspectRatio 1\n
                focalDistance 100\n
                height 44.932899\n\n
                */
            SetCamPosition(115.3f, 10.96f, 2.60f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetPerspective(100.0f, 170.5f, 60.27f);
        }break;

        case 7: {
            /*LEFT
                position - 71.182274 10.960546 2.6038406\n
                orientation 0.57735014 - 0.5773505 - 0.5773502  2.0943947\n
                nearDistance 16.166088\n
                farDistance 126.30847\n
                aspectRatio 1\n
                focalDistance 100\n
                height 44.932899\n\n}\n'
                */
            SetCamPosition(-71.18f, 10.96f, 2.60f);
            SetCenter(0.0f, 0.0f, 0.0f);
            SetPerspective(100.0f, 55.9f, 166.12f);
        }break;
        }


}
/**
*   Set camera type
*/
void Camera::setType(CameraList camTyp)
{
    camType_ = camTyp;
    active_ = true;
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
    return projectionMatrix_;
}
