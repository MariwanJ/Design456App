//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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

namespace FR {
    Fr_Transform::Fr_Transform() :
        m_position(0, 0, 0),
        m_x{ 0 },
        m_y{ 0 },
        m_z{ 0 }
    {
        m_Matrix = glm::mat4(1.0f);
        m_InverseMatrix = glm::inverse(m_Matrix);
    }

    void Fr_Transform::Rotate(float x, float y, float z, float angle) {
        m_Matrix = glm::rotate(m_Matrix, glm::radians(angle), glm::vec3(x, y, z));
        m_InverseMatrix = glm::inverse(m_Matrix);
    }

    void Fr_Transform::Rotate(glm::vec3 axis, float angle)
    {
        m_Matrix = glm::rotate(m_Matrix, glm::radians(angle), axis);
        m_InverseMatrix = glm::inverse(m_Matrix);
    }

    void Fr_Transform::Translate(glm::vec3 value) {
        m_Matrix = glm::translate(glm::mat4{ 1 }, value);
        m_InverseMatrix = glm::inverse(m_Matrix);
    }

    void Fr_Transform::Translate(float x, float y, float z) {
        m_x = x; m_y = y; m_z = z;
        m_Matrix = glm::translate(glm::mat4{ 1 }, glm::vec3(x, y, z));
        m_InverseMatrix = glm::inverse(m_Matrix);
    }

    void Fr_Transform::Scale(float x, float y, float z) {
        m_Matrix = glm::scale(m_Matrix, glm::vec3(x, y, z));
        m_InverseMatrix = glm::inverse(m_Matrix);
    }

    void Fr_Transform::Scale(glm::vec3 value) {
        m_Matrix = glm::scale(m_Matrix, value);
        m_InverseMatrix = glm::inverse(m_Matrix);
    }

    glm::mat4 Fr_Transform::GetViewMatrix() {
        return m_Matrix;
    }

    glm::mat4 Fr_Transform::GetInverseViewMatrix() {
        return m_InverseMatrix;
    }

    void Fr_Transform::Position(float x, float y, float z) {
        m_position = glm::vec3(x, y, z);
        Translate(m_position);
    }

    void Fr_Transform::Position(glm::vec3 pos)
    {
        m_position = pos;
        Translate(pos);
    }

    glm::vec3 Fr_Transform::Position() {
        return m_position;
    }
}