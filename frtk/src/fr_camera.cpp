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
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <fr_camera.h>
#include <fr_window.h>
#include <cassert>

namespace FR {
    const char* camNames[TOTAL_CAMS] = { "Perspective","Orthographic","Top","Bottom","Front","Rear","Right","Left" };
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

    float Fr_Camera::m_aspect_ratio = 1.9f;

    Fr_Camera::Fr_Camera() : Fr_Transform(),
        m_position{ 15.f, 11.f,  102.f },
        m_direction{ -.098f, -1.372f, 0.0f },
        m_up{ -58.84f, 628.451f, 29.412f },
        m_fovy{ 102.f },
        m_znear{ 0.01f },
        m_zfar{ 100000.f },
        m_OrthographicSize{ 10.f },
        m_ProjectionMatrix(glm::perspective(glm::radians(m_fovy), m_aspect_ratio, m_znear, m_zfar)), 
        m_camType(PERSPECTIVE) {
        int width, height;

        //This should not happen
        GLFWwindow* g = Fr_Window::getCurrentGLWindow();
        assert(g != nullptr);

        if (g == nullptr)
            return;
        glfwGetWindowSize(g, &width, &height);
        if (height != 0 && width != 0)      
            m_aspect_ratio = float(width) / float(height);
    }

    void Fr_Camera::SetCamPosition(float x, float y, float z) {
        m_position = glm::vec3(x, y, z);
    }
    glm::vec3 Fr_Camera::GetCamPosition() const
    {
        return m_position;
    }
    glm::vec3 Fr_Camera::GetCamDirection() const
    {
        return m_direction;
    }

    bool Fr_Camera::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        if (!m_active)
            return false;

        // Ensure the current GLFW window is valid
        GLFWwindow* g = Fr_Window::getCurrentGLWindow();
        assert(g != nullptr);

        int w, h;
        if (glfwGetWindowAttrib(g, GLFW_ICONIFIED)) {
            m_aspect_ratio = 1.9f;
        }
        else {
        glfwGetWindowSize(g, &w, &h);
        if (h != 0 && w != 0)
            m_aspect_ratio = static_cast<float>(w) / static_cast<float>(h);
            }
        // Set up projection matrix based on camera type
        if (m_camType == ORTHOGRAPHIC) {
            float orthoLeft = -m_OrthographicSize * m_aspect_ratio * 0.75f;
            float orthoRight = m_OrthographicSize * m_aspect_ratio * 0.75f;
            float orthoBottom = -m_OrthographicSize * 0.5f;
            float orthoTop = m_OrthographicSize * 0.5f;
            projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_znear, m_zfar);
        }
        else {
            if (m_aspect_ratio == 0)
                m_aspect_ratio = 1.9f; //avoid getting error
            projection = glm::perspective(glm::radians(m_fovy), m_aspect_ratio, m_znear, m_zfar);
        }

        m_ProjectionMatrix = projection;
        updateViewMatrix();         // Ensure this updates m_ViewMatrix correctly
        modelview = m_ViewMatrix;

        return true;
    }
 

    /**
     * Direct center of the camera.
     *
     * \param x : x axis location
     * \param y : y axis location
     * \param z : z axis location
     */
    void Fr_Camera::SetDirection(float x, float y, float z) {
        m_direction = glm::vec3(x, y, z);
        updateViewMatrix();
    }

    /**
     * Up value of the camera.
     *
     * \param x : x axis location
     * \param y : y axis location
     * \param z : z axis location
     */
    void Fr_Camera::SetUp(float x, float y, float z) {
        m_up = glm::vec3(x, y, z);
        updateViewMatrix();
    }
    /**
     * Set fovy, znear and z far values.
     *
     * \param fovy : Focal of view value
     * \param znear :  Z - Near value
     * \param zfar : z - Far value
     */
    void Fr_Camera::SetPerspective(float fovy, float znear, float zfar) {
        m_fovy = fovy;      //LEFT
        m_znear = znear;    //BOTTOM
        m_zfar = zfar;      //TOP
        updateViewMatrix();
    }
    /**
     * Get camera configurations.
     *
     * \param data ref variable keeps the configuration
     */
    void Fr_Camera::getCamData(userData_& data)
    {
        data.aspectRatio_ = m_aspect_ratio;
        data.camm_position = m_position;
        data.camType_ = m_camType;
        data.direction_ = m_direction;
        data.fovy_ = m_fovy;
        data.up_ = m_up;
        data.zfar_ = m_zfar;
        data.znear_ = m_znear;
        data.orthoSize_ = m_OrthographicSize;
    }

    void Fr_Camera::setCamData(userData_& data)
    {
        //aspectRatio_ = data.aspectRatio_;
        m_position = data.camm_position;
        m_camType = data.camType_;
        m_direction = data.direction_;
        m_fovy = data.fovy_;
        m_up = data.up_;
        m_zfar = data.zfar_;
        m_znear = data.znear_;
        m_OrthographicSize = data.orthoSize_;
        updateViewMatrix();
    }

    /**
     *
     * Home values.
     *
     */

    void Fr_Camera::setupCameraHomeValues() {
        //TODO CHECK ME !! 
        m_zfar = 10000.0f;
        m_znear = 0.01f;

        switch (int(m_camType)) {
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
            SetCamPosition(0.0f, -120.0f, 60.0f);
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 0.0f, 1.f);
            SetPerspective(45.0f, 0.01f, 10000.f);
        }break;
        case 1: {
            //ORTHOGRAPHIC

            SetCamPosition(17.46f, -149.46f, 135.46f);
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 0.0f, 1.0f);
            SetPerspective(30.248f, 0.01f, 10000.f);
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
            SetCamPosition(0.f, 0.f, 100.f);
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 1.f, 0.0f);
            SetPerspective(45.f, 0.01f, 10000.0f);
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
            SetCamPosition(0.0f, 0.0f, -100.0f);
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 1.0f, 0.f);
            SetPerspective(65, 0.01f, 10000.0f);
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
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 0.0f, 1.0f);
            SetPerspective(45.0f, 0.01f, 10000.0f);
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
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 0.0f, 1.f);
            SetPerspective(45.0f, 0.01f, 10000.0f);
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
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 0.0f, 1.f);
            SetPerspective(45.0f, 0.01f, 10000.0f);
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
            SetDirection(0.0f, 0.0f, 0.0f);
            SetUp(0.0f, 0.0f, 1.0f);
            SetPerspective(45.0f, 0.01f, 10000.0f);
        }break;
        }
       // m_up = glm::normalize(m_up);
        updateViewMatrix();
    }
    /**
    *   Set camera type
    */
    void Fr_Camera::setType(uint8_t camTyp)
    {
        m_camType = camTyp;
        m_active = true;
    }
    /**
     *
     * Set camera type which affects the setup function.
     * \return
     */
    uint8_t  Fr_Camera::getType() const
    {
        return m_camType;
    }

    glm::mat4 Fr_Camera::getProjection()
    {
        //Projection Matrix change these 3D world into 2D display
        if (m_camType == ORTHOGRAPHIC) {
            float orthoLeft = -m_OrthographicSize * m_aspect_ratio * 0.75f;
            float orthoRight = m_OrthographicSize * m_aspect_ratio * 0.75f;
            float orthoBottom = -m_OrthographicSize * 0.5f;
            float orthoTop = m_OrthographicSize * 0.5f;
            m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_znear, m_zfar);
        }
        else {
            m_ProjectionMatrix = glm::perspective(glm::radians(m_fovy), m_aspect_ratio, m_znear, m_zfar);
        }
        return m_ProjectionMatrix;
    }

    void Fr_Camera::updateViewMatrix() {
        m_ViewMatrix = glm::lookAt(m_position, m_direction, m_up);
        m_InverseViewMatrix = glm::inverse(m_ViewMatrix);
    }

    glm::mat4 Fr_Camera::GetViewMatrix() {
        updateViewMatrix();
        return m_ViewMatrix;
    }
 

    void Fr_Camera::SetOrthographicSize(float size_)
    {
        m_OrthographicSize = size_;
        updateViewMatrix();
    }

    float Fr_Camera::getOrthgraphicSize()
    {
        return m_OrthographicSize;
    }

    float Fr_Camera::getRatio() const
    {
        return m_aspect_ratio;
    }

    glm::mat4 Fr_Camera::GetInverseViewMatrix() {
        updateViewMatrix();
        return m_InverseViewMatrix;
    }
}