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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#include "Application.h"

/* Scene and engine*/
static Scene* scene = nullptr;

void Fr_GL3Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    this->_w = width;
    _h = height;
    if (s_GladInitialized && s_GLFWInitialized) {
        glViewport(0, 0, _w, _h);
    }
}

void Fr_GL3Window::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Fr_GL3Window::cursor_position_callback(GLFWwindow* win, double xpos, double ypos)
{
    /*
        if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            return;
        }
     */
    auto shftL = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT);
    auto shftR = glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT);

    if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_LEFT && FR::glfw_MouseClicked == 1) {
        LeftMouseClick(xpos, ypos);
    }
    else if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_MIDDLE && FR::glfw_MouseClicked == 1) {
        if (shftL == GLFW_PRESS || shftR == GLFW_PRESS) {
            cameraPAN(xpos, ypos);
        }
        else {
            cameraRotate(xpos, ypos);
        }
    }
    else if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT)
    {
        FR::glfw_e_x = xpos;
        FR::glfw_e_y = ypos;
    }
    else {
            FR::glfw_MouseButton = false;
            FR::glfw_e_x = xpos;
            FR::glfw_e_y = ypos;
        }
}

void Fr_GL3Window::cursor_enter_callback(GLFWwindow*, int entered)
{
}

void Fr_GL3Window::mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
    if (GLFW_PRESS == action) {
        FR::glfw_MouseClicked = 1; //Pressed
    }
    else {
        FR::glfw_MouseClicked = 0; //Released
    }
    FR::glfw_MouseButton = button;
}

void Fr_GL3Window::scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameras[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    float fov;
    userData_ data;
    activeCamera.camera->getUserData(data);
    fov = data.fovy_;
    fov = fov - yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > MAX_FOV_ZOOM)
        fov = MAX_FOV_ZOOM;
    data.fovy_ = fov;
    activeCamera.camera->setUserData(data);
}

void Fr_GL3Window::cameraPAN(double xpos, double ypos)
{
    if (MouseOnce)
    {
        FR::glfw_e_x = xpos;
        FR::glfw_e_y = ypos;
        MouseOnce = false;
    }

    float xoffset = xpos - FR::glfw_e_x;
    float yoffset = FR::glfw_e_y - ypos;
    FR::glfw_e_x = xpos;
    FR::glfw_e_y = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.999990f)
        pitch = 89.999990f;
    if (pitch < -89.999990f)
        pitch = -89.999990f;

    glm::vec3 direction;

    //std::cout << pitch << "pitch yaw " << yaw << std::endl;
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameras[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    userData_ data;
    activeCamera.camera->getUserData(data);
    data.direction_.x = 10*cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    data.direction_.y = 10*sin(glm::radians(pitch));
    data.direction_.z =  sin(glm::radians(yaw)) * cos(glm::radians(pitch));
   // data.direction_ = glm::normalize(data.direction_);
    activeCamera.camera->setUserData(data);
}

void Fr_GL3Window::cameraRotate(double xpos, double ypos)
{
    userData_ data;
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameras[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    activeCamera.camera->getUserData(data);

    if (MouseOnce)
    {
        FR::glfw_e_x = xpos;
        FR::glfw_e_y = ypos;
        MouseOnce = false;
        radiusXYZ = sqrt(data.camPosition_.x * data.camPosition_.x +
                        data.camPosition_.y * data.camPosition_.y+
                        data.camPosition_.z * data.camPosition_.z);
 
    }

    float delta_X = xpos - FR::glfw_e_x;
    float delta_Y = FR::glfw_e_y - ypos;
    FR::glfw_e_x = xpos;
    FR::glfw_e_y = ypos;
    float sensitivity = 0.2f;
  
    yaw += delta_X * sensitivity;
    pitch += delta_Y * sensitivity;
    
    if (pitch > 89.999990f)
        pitch = 89.999990f;
    if (pitch < -89.999990f)
        pitch = -89.999990f;
        

    glm::vec3 direction;
    //std::cout << pitch << "pitch yaw " << yaw << std::endl;
    data.camPosition_.x =radiusXYZ *cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    data.camPosition_.y = radiusXYZ *cos(glm::radians(yaw)) * sin(glm::radians(pitch));
    data.camPosition_.z = radiusXYZ* sin(glm::radians(yaw)) ;
    activeCamera.camera->setUserData(data);
}

void Fr_GL3Window::LeftMouseClick(double xoffset, double yoffset)
{
}

void Fr_GL3Window::RightMouseClick(double xoffset, double yoffset)
{
}

void Fr_GL3Window::joystick_callback(int jid, int events)
{
}

Application::Application(int x, int y, int w, int h, const char* l) :Fr_GL3Window(x, y, w, h, l)
{
}

Application::~Application()
{
}
#include <fr_icons.h>
int Application::run(int argc, char** argv)
{
    std::string fname = "R";

    auto n = loadImage();
    std::shared_ptr<BYTE> IMG = n.getImage("nofile");
    createGLFWwindow();

    return GLFWrun();
}