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

#include <glm/gtx/transform.hpp>
#include "Manipulator.h"
#include<glad/glad.h>

//Scroll zoomming scale - default is 10.0 
float Manipulator::kZoomScale = 50.0f;

Manipulator::Manipulator() :
    reference_(0, 0, 0),
    matrix_(1.0),
    inv_(1.0),
    operation_{ Operation::kNone },
    x_{ 0 },
    y_{ 0 },
    v_(0, 0, 0),
    invertX_{ false },
    invertY_{ false } {
}

glm::mat4 Manipulator::GetMatrix(const glm::vec3& look_dir) {
    glm::vec3 manip_dir = glm::vec3(0, 0, -1);
    if (glm::length(look_dir - manip_dir) < 0.01)
        return glm::translate(reference_)
        * matrix_
        * glm::translate(-reference_);

    glm::vec3 w = glm::cross(look_dir, manip_dir);
    float theta = asin(glm::length(w));
    return glm::translate(reference_)
        * glm::rotate(-theta, w)
        * matrix_
        * glm::rotate(theta, w)
        * glm::translate(-reference_);
}

glm::mat4 Manipulator::GetInverse() {
    return glm::translate(-reference_) * matrix_ * glm::translate(reference_);
}

void Manipulator::SetReferencePoint(float x, float y, float z) {
    reference_ = glm::vec3(x, y, z);
}

void Manipulator::GLFWMouse(int button, int state, double x, double y) {
    SetOperation<0, Operation::kRotation>(button, state, x, y);  //mouse move + right click
    SetOperation<1, Operation::kZoom>(button, state, x, y);   ///Mouse move+leftclick
}

void Manipulator::SetInvertAxis(bool invertX, bool invertY) {
    invertX_ = invertX;
    invertY_ = invertY;
}

void Manipulator::GLFWMotion(int x, int y) {
    if (operation_ == Operation::kNone)
        return;

    if (operation_ == Operation::kRotation) {
        glm::vec3 v = computeSphereCoordinates(x, y);
        glm::vec3 w = glm::cross(v_, v);
        float theta = asin(glm::length(w));
        if (theta != 0)
            matrix_ = glm::rotate(theta, w) * matrix_;
        v_ = v;
    }
    /*    Scroll will do this job
    else if (operation_ == Operation::kZoom) {
        int vp[4];
        glGetIntegerv(GL_VIEWPORT, vp);
        float dy = y - y_;
        float f = dy / vp[3];
        float scale = 1 + kZoomScale * f;
        matrix_ = glm::scale(glm::vec3(scale, scale, scale)) * matrix_;
    }
    */
    inv_ = glm::inverse(matrix_);
    x_ = x;
    y_ = y;
}
/**
*   Mouse scroll - Zomming 
*/
void Manipulator::GLFWScroll(int x, int y) {

    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    float dy = y;
    float f = dy / vp[3];
    float scale = 1 + kZoomScale * f;
    matrix_ = glm::scale(glm::vec3(scale, scale, scale)) * matrix_;
    inv_ = glm::inverse(matrix_);
    x_ += x;
    y_ += y;
}

double Manipulator::get_X() const
{
    return x_;
}

double Manipulator::get_Y() const
{
    return y_;
}

void Manipulator::setZommingScale(float _scale)
{
    kZoomScale = _scale;
}

template<int k_button, Manipulator::Operation k_operation>
void Manipulator::SetOperation(int button, int state, double x, double y) {            ///TODO FIXME : CHANGE THE STATE TO A BETTER AND MEANINGSFULL ENUM.
    if (button == k_button) {
        if (state == 0 && operation_ == Operation::kNone) {
            operation_ = k_operation;
            x_ = x;
            y_ = y;
            v_ = computeSphereCoordinates(x, y);
        }
        else if (state == 1 && operation_ == k_operation) {
            operation_ = Operation::kNone;
        }
    }
}

glm::vec3 Manipulator::computeSphereCoordinates(double x, double y) {
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    const float w = vp[2];
    const float h = vp[3];

    if (invertX_) x = w - x;
    if (invertY_) y = h - y;

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