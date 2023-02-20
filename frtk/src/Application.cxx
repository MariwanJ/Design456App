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
    if (s_GladInitialized && s_GLFWInitialized) {
        glViewport(0, 0, _wGl, _hGl);
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
    if (button == 0 || button == 1)
        if (win != nullptr) {
            auto activeCameraTrans = FR::globalP_pWindow->cameras[(unsigned int)FR::globalP_pWindow->active_camera_];
            if (activeCameraTrans->getNodes().size() > 1) {
                assert("Camera Transform should have only one child. Cannot continue!\n");
            }
            auto camera_ = std::dynamic_pointer_cast<Camera> (activeCameraTrans->getNode(0));// There must be only one and the child is the camera
            auto manipulator_ = camera_->getManipulator();
            manipulator_->GLFWMouse(button, FR::glfw_MouseClicked, cposx, cposy);
            manipulator_->GLFWMotion(cposx, cposy);
            FR::globalP_pWindow->scene->RenderScene();
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
    auto activeCameraTrans = FR::globalP_pWindow->cameras[(unsigned int)FR::globalP_pWindow->active_camera_];
    if (activeCameraTrans->getNodes().size() > 1) {
        assert("Camera Transform should have only one child. Cannot continue!\n");
    }
    auto camera_ = std::dynamic_pointer_cast<Camera> (activeCameraTrans->getNode(0));// There must be only one and the child is the camera
    auto manipulator_ = camera_->getManipulator();
    x = manipulator_->get_X();
    y = manipulator_->get_Y();
    if (win != nullptr) {
        manipulator_->GLFWScroll(xoffset, yoffset);
        FR::globalP_pWindow->scene->RenderScene();
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

int Application::run(int argc, char** argv)
{

    createGLFWwindow();
    return GLFWrun();
}
