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
#include <fr_transform.h>

Transform::Transform() :
    m_Position(0, 0, 0),active_(true),
    x_{ 0 },
    y_{ 0 },
    z_{ 0 },
    v_(0, 0, 0),
    invertX_{ false },
    invertY_{ false }
{
    m_Matrix = glm::mat4(1.0f);
    m_Inverse = glm::inverse(m_Matrix);
    
}

void Transform::Rotate(float x, float y, float z, float angle) {
    m_Matrix = glm::rotate(m_Matrix, glm::radians(angle), glm::vec3(x, y, z));
    m_Inverse = glm::inverse(m_Matrix);
}

void Transform::Rotate(glm::vec3 axis, float angle)
{
    m_Matrix = glm::rotate(m_Matrix, glm::radians(angle), axis);
    m_Inverse = glm::inverse(m_Matrix);
}

void Transform::Translate(glm::vec3 value) {
    m_Matrix = glm::translate(glm::mat4{ 1 }, value);
    m_Inverse = glm::inverse(m_Matrix);
}

void Transform::Translate(float x, float y, float z) {
    x_ = x; y_ = y; z_ = z;
    m_Matrix = glm::translate(glm::mat4{ 1 }, glm::vec3(x, y, z));
    m_Inverse = glm::inverse(m_Matrix);
}

void Transform::Scale(float x, float y, float z) {
    m_Matrix = glm::scale(m_Matrix, glm::vec3(x, y, z));
    m_Inverse = glm::inverse(m_Matrix);
}

void Transform::Scale(glm::vec3 value) {
    m_Matrix = glm::scale(m_Matrix, value);
    m_Inverse = glm::inverse(m_Matrix);
}

glm::mat4 Transform::GetMatrix() {
    return m_Matrix;
}

glm::mat4 Transform::GetInverse() {
    return m_Inverse;
}

void Transform::SetPosition(float x, float y, float z) {
    m_Position = glm::vec3(x, y, z);
    Translate(m_Position);
}

void Transform::SetPosition(glm::vec3 pos)
{
    m_Position = pos;
    Translate(pos);
}


void Transform::SetInvertAxis(bool invertX, bool invertY) {
    invertX_ = invertX;
    invertY_ = invertY;
}

float Transform::get_X() const
{
    return x_;
}

float Transform::get_Y() const
{
    return y_;
}
float Transform::get_Z() const
{
    return z_;
}

glm::vec3 Transform::computeSphereCoordinate(double x, double y) {
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