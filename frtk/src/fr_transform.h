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
// copipies of the Software, and to permit persons to whom the Software is
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
#ifndef FR_TRANSFORM_H
#define FR_TRANSFORM_H
#include <fr_core.h>

#include <memory>
namespace FR {
    class FRTK_API Fr_Transform {
    public:
        /**
         * Constructor
         * Loads the identity by default
         */
        Fr_Transform();

        /**
         * Multiply the current matrix by a rotation matrix
         */
        virtual void Rotate(float x, float y, float z, float angle);

        /**
         * Multiply the current matrix by a rotation matrix
         */
        virtual void Rotate(glm::vec3 axis, float angle);

        virtual void Translate(glm::vec3 v);

        /**
         * Multiply the current matrix by a translation matrix
         */
        void Translate(float x, float y, float z);

        /**
         * Multiply the current matrix by a translation matrix
         */
        virtual void Scale(float x, float y, float z);

        virtual void Scale(glm::vec3 value);

    protected:
        //Camera ViewMatrix and it's inverse
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_InverseViewMatrix;

    public:

         /**
          * Accumulates the inverse of the manipulator matrix
          */
        virtual glm::mat4 GetViewMatrix();
        virtual glm::mat4 GetInverseViewMatrix();

        /**
         * Sets the reference point (world center)
         */
        void SetPosition(float x, float y, float z);

        void SetPosition(glm::vec3 pos);

        /**
         * Sets whether each axis is inverted or not
         */
        void SetInvertAxis(bool invertX, bool invertY = false);

        bool isActive(void);
        void isActive(bool val);
    protected:
        bool m_active;
    private:
        enum class Operation {
            kRotation,  //Mouse click and drag
            kZoom,       //Left mouse and drag
            kNone       //nothing
        };
  
        /** Computes the sphere vector for rotation */
        glm::vec3 computeSphereCoordinate(double x, double y);
  
        glm::vec3 m_Position;
        Operation operation_;
        float x_, y_, z_;
        glm::vec3 v_;
        bool invertX_, invertY_;
    };
}

#endif
