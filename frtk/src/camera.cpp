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
#include <Camera.h>
#include <Manipulator.h>

Camera::Camera() :
    eye_{1, 0, 0},
    center_{0, 0, 0},
    up_{0, 1, 0},
    fovy_{50},
    znear_{1},
    zfar_{100},
    manipulator_{} {
}

void Camera::SetEye(float x, float y, float z) {
    eye_ = glm::vec3(x, y, z);
}

void Camera::SetCenter(float x, float y, float z) {
    center_ = glm::vec3(x, y, z);
}

void Camera::SetUp(float x, float y, float z) {
    up_ = glm::vec3(x, y, z);
}

void Camera::SetPerspective(float fovy, float znear, float zfar) {
    fovy_ = fovy;
    znear_ = znear;
    zfar_ = zfar;
}

void Camera::SetManipulator(std::unique_ptr<Manipulator> manipulator) {
    manipulator_ = std::move(manipulator);
}

bool Camera::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
    if (!active_)
        return false;

    int vp[4]; 
    glGetIntegerv(GL_VIEWPORT, vp); 
    projection = glm::perspective((float)(fovy_ * M_PI / 180.0),(float)vp[2]/vp[3], znear_, zfar_);
    modelview = glm::lookAt(eye_, center_, up_);
    if (manipulator_)
        modelview *= manipulator_->GetMatrix(glm::normalize(center_ - eye_));

    return true;
}

