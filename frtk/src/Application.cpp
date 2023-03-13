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
    int button;
    if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_LEFT) {
        button = 0;//TODO FIDME
    }
    else if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT)
    {
        button = 1;//TODO FIDME
        FR::glfw_MouseButton = -1;
    }
    else {
        button = -1;
        FR::glfw_MouseButton = -1;
    }
    double cposx, cposy;
    glfwGetCursorPos(win, &cposx, &cposy);
    FR::glfw_e_x = cposx;
    FR::glfw_e_y = cposy;
    return;//temp code
    if (button == 0 || button == 1)
        if (win != nullptr) {
            auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameras[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
            auto manipulator_ = activeCamera.manipulator;
            manipulator_->GLFWMouse(button, FR::glfw_MouseClicked, cposx, cposy);
            manipulator_->GLFWMotion(cposx, cposy);
            Fr_GL3Window::getfr_Gl3Window()->scene->RenderScene();
            button = -1;
        }
}

void Fr_GL3Window::cursor_enter_callback(GLFWwindow*, int entered)
{
}

void Fr_GL3Window::mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
    if (GLFW_PRESS == action) {
        FR::glfw_MouseClicked = 0; //Pressed
    }
    else if (GLFW_RELEASE == action) {
        FR::glfw_MouseClicked = 1; //Released
    }
    FR::glfw_MouseButton = button;
}

void Fr_GL3Window::scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
    double x, y;
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameras[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    auto manipulator_ = activeCamera.manipulator;
    x = manipulator_->get_X();
    y = manipulator_->get_Y();
    if (win != nullptr) {
        manipulator_->GLFWScroll(xoffset, yoffset);
    }
}

void Fr_GL3Window::joystick_callback(int jid, int events)
{

}


Application::Application(int x, int y, int w, int h, const char* l):Fr_GL3Window(x,y,w,h,l)
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
