//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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
#include <fr_transform.h>
#include <glm/glm.hpp>

namespace FR {
    /*
        R= Right Vector
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
     * Scene's camera- Must be a subclass of Transform to achieve translation
     */

    class FRTK_API Fr_Camera : public Fr_Transform {
        friend Fr_Window;
    public:

        Fr_Camera();

        //Disallow copy & equal operator 
        Fr_Camera(const Fr_Camera& camera) = delete;
        Fr_Camera& operator=(const Fr_Camera& other) = delete;

        void SetCamPosition(float x, float y, float z);
        glm::vec3 GetCamPosition() const;

        glm::vec3 GetCamDirection() const;

        void setupCameraHomeValues();

        void SetDirection(float x, float y, float z);

        void SetUp(float x, float y, float z);

        /**
         * .
         *
         * \param fovy : type float, Lens of the camera , normally should be round 45
         * \param znear : type float, normally is near to zero, but cannot be zero
         * \param zfar  : type float, normally is about 1000
         */
        void SetPerspective(float fovy, float znear, float zfar);

        void getCamData(userData_& data);
        void setCamData(userData_& data);

        /**
         * Sets the camera
         * Returns true if the camera has been set
         * Returns the camera info by reference
         */
        virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

        /**
        *   Setup camera type , default perspective
        */
        void setType(uint8_t camTyp = PERSPECTIVE);

        uint8_t  getType() const;

        glm::mat4 getProjection();
        void updateViewMatrix();

        virtual glm::mat4 GetViewMatrix();
        glm::mat4 GetInverseViewMatrix();

        void SetOrthographicSize(float size);
        float getOrthgraphicSize();

    private:

        uint8_t m_camType;
        glm::vec3 m_position;
        glm::vec3 m_direction;
        glm::vec3 m_up;   //RIGHT
        float m_fovy;     //LEFT
        float m_znear;    //BOTTOM
        float m_zfar;     //TOP
        static float m_aspect_ratio;      //must be static as all cameras have the same ratio
        glm::mat4 m_ProjectionMatrix;
        float m_OrthographicSize;
    };
}

#endif
