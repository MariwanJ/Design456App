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

#ifndef FR_CAMERA_H
#define FR_CAMERA_H

#include<frtk.h>
#include<fr_core.h>
#include<fr_transform.h>
#include <fr_node.h>
#include <glm/glm.hpp>

/*
    R= Righ Vector 
    U= Up Vector 
    D=  Direction Vector
    P=  Camera position vector

                        Rx  Ry  Rz  0               1   0   0   -Px
            LookAt =    Ux  Uy  Uz  0       *       0   1   0   -Py
                        Dx  Dy  Dz  0               0   0   1   -Pz
                        0   0   0   1               0   0   0   1

                        
*/






class Manipulator;


/**
 * Scene's camera- Must be a subclass of Transform to achive translation
 */
class Camera : public Transform {
public:
    /**
     * Constructor
     */
    Camera();

    /**
     * Sets the eye coordinates
     * Default = (1, 0, 0)
     */
    void SetCamPosition(float x, float y, float z);
    void setupCameraHomeValues();
    /**
     * Sets the center coordinates
     * Default = (0, 0, 0)
     */
    void SetCenter(float x, float y, float z);

    /**
     * Sets the up coordinates
     * Default = (0, 1, 0)
     */
    void SetUp(float x, float y, float z);

    /**
     * Sets the perspective parameters
     * Default 60, 1, 100
     */
    void SetPerspective(float fovy, float znear, float zfar);

    void getUserData(userData_& data);
    void setUserData(userData_& data);
    /**
     * Sets the manipulator
     */
    void SetTransform(std::shared_ptr<Transform> transform);

    /**
     * Get the manipulator that is associated with the camera.
     * 
     * \return pointer to manipulator associated with the camera
     */
    std::shared_ptr<Transform> getTransform();

    /**
     * Sets the camera
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

    /**
    *   Setup camera type , default perspective
    */
    void setType(CameraList camTyp = CameraList::PERSPECTIVE);

    CameraList  getType() const;

    CameraList getCameraType();

    glm::mat4 getPorjection();
    glm::mat4 getModelView();
private:
    glm::mat4 modelview_;
    CameraList camType_ ;
    glm::vec3 camPosition_;
    glm::vec3 direction_;
    glm::vec3 up_;  //RIGHT
    float fovy_;    //LEFT
    float znear_;   //BOTTOM
    float zfar_;   //TOP 
    float aspectRatio_;
    std::shared_ptr<Transform> transform_;
    glm::mat4 projectionMatrix_;
};

#endif

