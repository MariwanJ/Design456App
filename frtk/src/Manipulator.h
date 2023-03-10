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
#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include<frtk.h>
#include<Fr_Core.h>

#include <glm/glm.hpp>

class Manipulator {
public:
    /**
     * Constructor
     */
    Manipulator();
    
    /**
     * Accumulates the manipulator matrix
     */
    glm::mat4 GetMatrix(const glm::vec3& look_dir = glm::vec3(0, 0, -1));

    /**
     * Accumulates the inverse of the manipulator matrix
     */
    glm::mat4 GetInverse();

    /**
     * Sets the reference point (world center)
     */
    void SetReferencePoint(float x, float y, float z);

    /**
     * Sets whether each axis is inverted or not
     */
    void SetInvertAxis(bool invertX, bool invertY = false);

    /**
     * Mouse button function
     */
    void GLFWMouse(int button, int state, double x, double y);

    /**
     * Mouse motion function
     */
    void GLFWMotion(int x, int y);
    void GLFWScroll(int x, int y);

    double get_X()const;
    double get_Y()const;
    void setZommingScale(float scale);

private:
    enum class Operation {
        kRotation,  //Mouse click and drag
        kZoom,       //Left mouse and drag
        kNone       //nothing
    };

    static float kZoomScale;

    /** Verifies the k_button state and sets the k_operation */
    template<int k_button, Operation k_operation>
    void SetOperation(int button, int state, double x,double y);

    /** Computes the sphere vector for rotation */
    glm::vec3 computeSphereCoordinates(double x, double y);

    glm::vec3 reference_;
    glm::mat4 matrix_;
    glm::mat4 inv_;
    Operation operation_;
    double x_, y_;
    glm::vec3 v_;
    bool invertX_, invertY_;
};

#endif

