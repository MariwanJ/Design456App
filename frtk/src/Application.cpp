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
#include <glm/gtx/transform.hpp>


//TODO: I don't see any reason to have these functions here any more - move them to other place
/* Scene and engine*/
static Scene* scene = nullptr;

void Fr_GL3Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    this->_w = width;
    _h = height;
    if (s_GladInitialized && s_GLFWInitialized) {
        glViewport(_x, _y, _w, _h);
    }
    WidgWindow->handle(FR::FR_WINDOW_RESIZE);
}
/*

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)

    window: A pointer to the GLFW window that received the event.
    key: The keyboard key that was pressed or released.
    scancode: The system-specific scancode of the key.
    action: The action that was performed on the key. It can be one of the following values:
        GLFW_PRESS: The key was pressed.
        GLFW_RELEASE: The key was released.
        GLFW_REPEAT: The key was held down and is being repeated.
    mods: Bit field describing which modifier keys (Shift, Control, Alt, Super) were held down.

*/
void Fr_GL3Window::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    m_GLFWevents = { -1,-1,-1,-1,-1};
    
    m_GLFWevents.lastKey = key;
    m_GLFWevents.lastAction = action;
    m_GLFWevents.lastMod = mods;
    m_GLFWevents.scancode = scancode;
    if (WidgWindow->handle(FR::FR_KEYBOARD) == 0) {
        m_GLFWevents = { -1,-1,-1,-1,-1 };  
        return;
    }
}

void Fr_GL3Window::mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
    //TODO FIX ME  - THIS IS NOT FINISHED - THIS AND MOUSE MOVEMENT IS NOT CORRECT
    m_GLFWevents.button = button;
    m_GLFWevents.lastAction = action;
    m_GLFWevents.lastMod = mods;

    if (GLFW_PRESS == action) {
        glfw_MouseClicked = 1; //Pressed
    }
    else {
        glfw_MouseClicked = 0; //Released
    }
    glfw_MouseButton = button;

    auto shftL = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT);
    auto shftR = glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT);

    if (glfw_MouseButton == GLFW_MOUSE_BUTTON_LEFT && glfw_MouseClicked == 1)
    {        //FRTK_CORE_INFO("MOUSE LEFT");
        LeftMouseClick(win,glfw_e_x, glfw_e_y );
        if (WidgWindow->handle(FR::FR_PUSH) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }
    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_LEFT && glfw_MouseClicked == 0)
    {
        //FRTK_CORE_INFO("MOUSE LEFT");
        LeftMouseRelease(win,glfw_e_x, glfw_e_y);
        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }

    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT && glfw_MouseClicked == 1)
    {
        RightMouseClick(win,glfw_e_x, glfw_e_y);
        if (WidgWindow->handle(FR::FR_PUSH) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }
    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT && glfw_MouseClicked == 0)
    {
        RightMouseRelease(win,glfw_e_x, glfw_e_y);
        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }

    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_MIDDLE && glfw_MouseClicked == 1)
    {
        //TODO : Not sure if widgets needs this event
        MiddMouseClick(win,glfw_e_x, glfw_e_y);
        if (WidgWindow->handle(FR::FR_PUSH) == 0) //Mouse click
            return;
    }

    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_MIDDLE && glfw_MouseClicked == 0)
    {
        //TODO : Not sure if widgets needs this event
        MiddMouseRelease(win,glfw_e_x, glfw_e_y);
        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click
            return;
    }
    MouseMovement(glfw_e_x, glfw_e_y);
    if (WidgWindow->handle(FR::FR_MOUSE_MOVE) == 0) //Mouse click
        return;
}
void Fr_GL3Window::cursor_position_callback(GLFWwindow* win, double xpos, double ypos)
{
        //Here we have mouse movement

    auto shftL = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT);
    auto shftR = glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT);
    glfw_e_x = xpos;
    glfw_e_y = ypos;

    if (glfw_MouseButton == GLFW_MOUSE_BUTTON_LEFT && glfw_MouseClicked == 1) 
    {
        if (WidgWindow->handle(FR::FR_LEFT_DRAG_PUSH)==0) //Mouse click
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;  //Events is consumed - no more action required
    }
    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_LEFT && glfw_MouseClicked == 0)
    {
        if (WidgWindow->handle(FR::FR_LEFT_DRAG_RELEASE) == 0) //Mouse click
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;  //Events is consumed - no more action required
    }

    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT && glfw_MouseClicked == 1)
    {
        if (WidgWindow->handle(FR::FR_RIGHT_DRAG_PUSH) == 0) //Mouse click
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;  //Events is consumed - no more action required
    }
    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT && glfw_MouseClicked == 0)
    {
 
        if (WidgWindow->handle(FR::FR_RIGHT_DRAG_RELEASE) == 0) //Mouse click
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;  //Events is consumed - no more action required
    }

    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_MIDDLE && glfw_MouseClicked == 1) 
    {
        if (shftL == GLFW_PRESS || shftR == GLFW_PRESS) {
         //   FRTK_CORE_INFO("MOUSE PAN");
            cameraPAN(win,xpos, ypos);
        }
        else {
         //   FRTK_CORE_INFO("MOUSE ROTATE");
            cameraRotate(win,xpos, ypos);
        }
        //TODO : Not sure if widgets needs this event
        if (WidgWindow->handle(FR::FR_PUSH) == 0) //Mouse click
            return;
    }

    else if (glfw_MouseButton == GLFW_MOUSE_BUTTON_MIDDLE && glfw_MouseClicked == 0)
    {
        //TODO : Not sure if widgets needs this event
        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;
    }
    
    if (WidgWindow->handle(FR::FR_MOUSE_MOVE) == 0) //Mouse click
        m_GLFWevents = { -1,-1,-1,-1,-1 };
        return;


}

void Fr_GL3Window::cursor_enter_callback(GLFWwindow*, int entered)
{
}


void Fr_GL3Window::scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameraList[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    userData_ data;
    activeCamera->getUserData(data);
    if (activeCamera->getType() == CameraList::ORTHOGRAPHIC) {
        data.orthoSize_ = data.orthoSize_ + yoffset * mouseDefaults.MouseScrollScale;
    }
    else
    {
        //Scroll zooming using the correct method of zooming. Use camera position by scaling the view-matrix
        float scale_;

        glm::mat4 matr = glm::lookAt(data.camPosition_, data.direction_, data.up_);
        if (yoffset < 0) {
            scale_ = 1 / mouseDefaults.MouseScrollScale;
        }
        else
        {
            scale_ = mouseDefaults.MouseScrollScale;
        }
        matr = glm::scale(matr, glm::vec3(scale_, scale_, scale_));
        glm::vec3 position, direction, up;
        glm::mat4 inverseViewMatrix = glm::inverse(matr);
        data.camPosition_ = glm::vec3(inverseViewMatrix[3]);
        glm::vec3 ddd = glm::vec3(inverseViewMatrix[2]);
        data.direction_ = -glm::vec3(inverseViewMatrix[2]);
        data.up_ = glm::vec3(inverseViewMatrix[1]);
    }
    activeCamera->setUserData(data);
}

void Fr_GL3Window::MouseMovement(double xoffset, double yoffset)
{
}

void Fr_GL3Window::cameraPAN(GLFWwindow* win, double xpos, double ypos)
{
    if (MouseOnce)
    {
        glfw_e_x = xpos * mouseDefaults.MouseXYScale;
        glfw_e_y = ypos * mouseDefaults.MouseXYScale;
        MouseOnce = false;
    }
    userData_ data;
    //std::cout << pitch << "pitch yaw " << yaw << std::endl;
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameraList[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];

    activeCamera->getUserData(data);
    radiusXYZ = sqrt(data.camPosition_.x * data.camPosition_.x +
        data.camPosition_.y * data.camPosition_.y +
        data.camPosition_.z * data.camPosition_.z);

    float xoffset = xpos * mouseDefaults.MouseXYScale - glfw_e_x;
    float yoffset = (glfw_e_y - ypos * mouseDefaults.MouseXYScale) * data.aspectRatio_;
    glfw_e_x = xpos * mouseDefaults.MouseXYScale;
    glfw_e_y = ypos * mouseDefaults.MouseXYScale;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.999990f)
        pitch = 89.999990f;
    if (pitch < -89.999990f)
        pitch = -89.999990f;

    glm::vec3 direction;
    //TODO : CHECK ME .. DO WE SHOULD HAVE BOTH OR ONE OF THEM??

    data.camPosition_.x = radiusXYZ * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    data.camPosition_.y = radiusXYZ * cos(glm::radians(yaw)) * sin(glm::radians(pitch));

    // data.camPosition_.x = radiusXYZ * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    // data.camPosition_.y = radiusXYZ * cos(glm::radians(yaw)) * sin(glm::radians(pitch));

     //data.direction_.z =  sin(glm::radians(yaw)) * cos(glm::radians(pitch));
     // data.direction_ = glm::normalize(data.direction_);
    activeCamera->setUserData(data);
}

void Fr_GL3Window::cameraRotate(GLFWwindow* win, double xpos, double ypos)
{
    userData_ data;
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameraList[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    activeCamera->getUserData(data);

    if (MouseOnce)
    {
        glfw_e_x = xpos * mouseDefaults.MouseXYScale;
        glfw_e_y = ypos * mouseDefaults.MouseXYScale;
        MouseOnce = false;
        radiusXYZ = sqrt(data.camPosition_.x * data.camPosition_.x +
            data.camPosition_.y * data.camPosition_.y +
            data.camPosition_.z * data.camPosition_.z);
    }

    float delta_X = xpos * mouseDefaults.MouseXYScale - glfw_e_x;
    float delta_Y = (ypos * mouseDefaults.MouseXYScale - glfw_e_y);
    glfw_e_x = xpos * mouseDefaults.MouseXYScale;
    glfw_e_y = ypos * mouseDefaults.MouseXYScale;

    yaw += delta_X;
    pitch += delta_Y;

    if (pitch > 89.999990f)
        pitch = 89.999990f;
    if (pitch < -89.999990f)
        pitch = -89.999990f;

    glm::vec3 direction;
    //std::cout << pitch << "pitch yaw " << yaw << std::endl;
    data.camPosition_.x = radiusXYZ * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    data.camPosition_.y = radiusXYZ * cos(glm::radians(yaw)) * sin(glm::radians(pitch));
    data.camPosition_.z = radiusXYZ * sin(glm::radians(yaw));
    activeCamera->setUserData(data);
}

void Fr_GL3Window::LeftMouseClick(GLFWwindow* win, double xoffset, double yoffset)
{

}

void Fr_GL3Window::RightMouseClick(GLFWwindow* win, double xoffset, double yoffset)
{
}


void Fr_GL3Window::MiddMouseClick(GLFWwindow* win, double xoffset, double yoffset)
{

}

void Fr_GL3Window::LeftMouseRelease(GLFWwindow* win, double xoffset, double yoffset)
{

}

void Fr_GL3Window::RightMouseRelease(GLFWwindow* win, double xoffset, double yoffset)
{
}


void Fr_GL3Window::MiddMouseRelease(GLFWwindow* win, double xoffset, double yoffset)
{

}


void Fr_GL3Window::LeftMouseDRAG(GLFWwindow* win, double xoffset, double yoffset)
{

}

void Fr_GL3Window::RightMouseDRAG(GLFWwindow* win, double xoffset, double yoffset)
{
}


void Fr_GL3Window::MiddMouseDRAG(GLFWwindow* win, double xoffset, double yoffset)
{
}


void Fr_GL3Window::joystick_callback( int jid, int events)
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
    // std::string fname = "R";

    // auto n = loadImage();
     //std::shared_ptr<BYTE> IMG = n.getImage("nofile");
    createGLFWwindow();

    return GLFWrun();
}