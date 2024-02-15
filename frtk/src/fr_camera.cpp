//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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
#include <glm/gtx/transform.hpp>
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

float Camera::aspectRatio_ = 1.9;

Camera::Camera() : 
    camPosition_{ 15.f, 11.f,  102.f }, v_(0, 0, 0),
    direction_{ -.098f, -1.372f, 0.0f },
    up_{ -58.84f, 628.451f, 29.412f },
    fovy_{ 102.f }, m_Active(false),
    znear_{ 0.01 },
    zfar_{ 100000 },
    m_OrthographicSize{10},
    m_ProjectionMatrix(glm::perspective(glm::radians(fovy_), aspectRatio_, znear_, zfar_)),     //default
    camType_(CameraList::PERSPECTIVE) {
    int width, height;
    Fr_GL3Window* g = Fr_GL3Window::getfr_Gl3Window();
    glfwGetWindowSize(g->pWindow, &width, &height);
    aspectRatio_ = float(width) / float(height);
}

void Camera::SetCamPosition(float x, float y, float z) {
    camPosition_ = glm::vec3(x, y, z);
}
glm::vec3 Camera::GetCamPosition()
{
    return camPosition_;
}
bool  Camera::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
{
    if (!m_Active)
        return false;
 
    //FRTK_CORE_INFO(aspectRatio_);

    if (camType_ == CameraList::ORTHOGRAPHIC) {
        float aspect = Fr_GL3Window::getfr_Gl3Window()->getAspectRation();
        float orthoLeft = -m_OrthographicSize * aspectRatio_ * 0.5f;
        float orthoRight = m_OrthographicSize * aspectRatio_ * 0.5f;
        float orthoBottom = -m_OrthographicSize * 0.5f;
        float orthoTop = m_OrthographicSize * 0.5f;
        projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, znear_, zfar_);
    }
    else {
        projection = glm::perspective(glm::radians(fovy_), aspectRatio_, znear_, zfar_);
    }
    updateViewMatrix();
    modelview = m_Matrix;
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
    updateViewMatrix();
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
    updateViewMatrix();

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
    updateViewMatrix();
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
    data.orthoSize_ = m_OrthographicSize;
}

void Camera::setUserData(userData_& data)
{
    //aspectRatio_ = data.aspectRatio_;
    camPosition_ = data.camPosition_;
    camType_ = data.camType_;
    direction_ = data.direction_;
    fovy_ = data.fovy_;
    up_ = data.up_;
    zfar_ = data.zfar_;
    znear_ = data.znear_;
    m_OrthographicSize = data.orthoSize_;
    updateViewMatrix();
}

/**
 *
 * Home values.
 *
 */

void Camera::setupCameraHomeValues() {
    switch (int(camType_)) {
        //TODO: FIXME: If you create more than 8, you should add it here
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
        SetCamPosition(1.12f, -51.0f, 62.0f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetUp(-58.0f, 628.0f, 300.f);
        SetPerspective(45.0f, 0.429f, 100000.f);
    }break;
    case 1: {
        //ORTHOGRAPHIC

        SetCamPosition(17.46f, -149.46f, 135.46f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetPerspective(30.248f, 0.429f, 100000.f);
        SetOrthographicSize(45);
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
        SetCamPosition(-2.f, -8.f, -54.f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetUp(0.0f, 37.f, 0.0f);
        SetPerspective(45.f, 0.1f, 100000.0f);
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
        SetCamPosition(0.0f, 0.0f, -100.4f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetUp(0.0f, 0.1f, 10.f);
        SetPerspective(65, 0.10f, 100000.0f);
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
        SetCamPosition(0.0f, -90.0f, 0.0f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetUp(0.0f, 0.0f, .5f);
        SetPerspective(45.0f, 0.10f, 100000.0f);
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
        SetCamPosition(0.0f, 90.0f, 0.0f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetUp(0.0f, 0.0f, 10.f);
        SetPerspective(45.0f, 0.1f, 100000.0f);
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
        SetCamPosition(100.0f, 0.0f, 0.0f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetUp(0.0f, 0.0f, 0.1f);
        SetPerspective(45.0f, 0.10f, 100000.0f);
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
        SetCamPosition(-100.0f, 0.0f, 0.0f);
        SetCenter(0.0f, 0.0f, 0.0f);
        SetUp(0.0f, 0.0f, 0.1f);
        SetPerspective(45.0f, 0.10f, 100000.0f);
    }break;
    }
    updateViewMatrix();
}
/**
*   Set camera type
*/
void Camera::setType(CameraList camTyp)
{
    camType_ = camTyp;
    m_Active = true;
}
/**
 *
 * Set camera type which affects the setup function.
 * \return
 */
CameraList  Camera::getType() const
{
    return camType_;
}
 

glm::mat4 Camera::getPorjection()
{
    m_ProjectionMatrix = glm::perspective(glm::radians(fovy_), aspectRatio_, znear_, zfar_);
    return m_ProjectionMatrix;
}
void Camera::updateViewMatrix() {
    m_Matrix = glm::lookAt(camPosition_, direction_, up_);
    m_Inverse = glm::inverse(m_Matrix);
}

glm::mat4 Camera::GetViewMatrix() {
    updateViewMatrix();
    return m_Matrix;
}

void Camera::setViewMatrix(glm::mat4 &t)
{
    m_Matrix = t;
}


void Camera::SetOrthographicSize(float size_)
{
    m_OrthographicSize = size_;
    updateViewMatrix();
}

float Camera::getOrthgraphicSize()
{
    return m_OrthographicSize;
}

void Camera::isActive(bool val)
{
    m_Active = val;
}

bool Camera::isActive()
{
    return m_Active;
}
 

glm::mat4 Camera::GetInverseViewMatrix() {
    return m_Inverse;
}

glm::vec3 Camera::computeSphereCoordinates(int x, int y) {
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    Fr_GL3Window* win=Fr_GL3Window::getfr_Gl3Window();
    ImVec4 screenDim = win->getPortViewDimensions();
    const float w = screenDim.z;
    const float h = screenDim.w;
    const float radius = std::min(w / 2.0f, h / 2.0f);
    float vx = (x - w / 2.0f) / radius;
    float vy = (h - y - h / 2.0f) / radius;
    float vz = 0;

    const float dist = hypot(vx, vy);
    if (dist > 1.0f) {
        vx /= dist;
        vy /= dist;
    }
    else {
        vz = sqrt(1 - vx * vx - vy * vy);
    }

    return glm::vec3(vx, vy, vz);
}
