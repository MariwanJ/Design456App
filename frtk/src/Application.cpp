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
        mouseEvent.Pressed = 1; //Pressed
    }
    else {
        mouseEvent.Pressed = 0; //Released
    }
    mouseEvent.Button= button;

    auto shftL = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT);
    auto shftR = glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT);

    if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT && mouseEvent.Pressed== 1)
    {        //FRTK_CORE_INFO("MOUSE LEFT");
        LeftMouseClick(win );
        if (WidgWindow->handle(FR::FR_PUSH) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }
    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT && mouseEvent.Pressed == 0)
    {
        //FRTK_CORE_INFO("MOUSE LEFT");
        LeftMouseRelease(win);
        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }

    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_RIGHT && mouseEvent.Pressed == 1)
    {
        RightMouseClick(win);
        if (WidgWindow->handle(FR::FR_PUSH) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }
    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_RIGHT && mouseEvent.Pressed == 0)
    {
        RightMouseRelease(win);
        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }

    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_MIDDLE && mouseEvent.Pressed == 1)
    {
        //TODO : Not sure if widgets needs this event
        theta = phi = 0;
        MiddMouseClick(win);
        if (WidgWindow->handle(FR::FR_PUSH) == 0) //Mouse click
            return;
    }

    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_MIDDLE && mouseEvent.Pressed == 0)
    {
        //TODO : Not sure if widgets needs this event
        MiddMouseRelease(win);
        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click
            return;
    }

}
void Fr_GL3Window::cursor_position_callback(GLFWwindow* win, double xpos, double ypos)
{
        //Here we have mouse movement

    auto shftL = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT);
    auto shftR = glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT);
    //std::cout << "xpos= ypso=" << xpos << " " << ypos<<std::endl;

    if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT && mouseEvent.Pressed== 1)
    {
        LeftMouseDRAG(win, xpos, ypos);
        if (WidgWindow->handle(FR::FR_LEFT_DRAG_PUSH)==0) //Mouse click
            return;  //Events is consumed - no more action required
    }
    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT && mouseEvent.Pressed== 0)
    {
        LeftMouseDRAGrelease(win, xpos, ypos);
        if (WidgWindow->handle(FR::FR_LEFT_DRAG_RELEASE) == 0) //Mouse click
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;  //Events is consumed - no more action required
    }

    else if (mouseEvent.Button== GLFW_MOUSE_BUTTON_RIGHT && mouseEvent.Pressed== 1)
    {
        RightMouseDRAG(win, xpos,ypos);
        if (WidgWindow->handle(FR::FR_RIGHT_DRAG_PUSH) == 0) //Mouse click
            return;  //Events is consumed - no more action required
    }
    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_RIGHT && mouseEvent.Pressed== 0)
    {
        RightMouseDRAGrelease(win, xpos, ypos);
        if (WidgWindow->handle(FR::FR_RIGHT_DRAG_RELEASE) == 0) //Mouse click
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;  //Events is consumed - no more action required
    }

    else if (mouseEvent.Button== GLFW_MOUSE_BUTTON_MIDDLE && mouseEvent.Pressed == 1)
    {
        if (shftL == GLFW_PRESS || shftR == GLFW_PRESS) {
         //   FRTK_CORE_INFO("MOUSE PAN");
            cameraPAN(win,xpos, ypos);
            return;                                 //TODO: FR_WIDGET DOSEN'T GET THIS EVENT.. SHOULD WE?
        }
        else {
         //   FRTK_CORE_INFO("MOUSE ROTATE");           //TODO: FR_WIDGET DOSEN'T GET THIS EVENT.. SHOULD WE?
            cameraRotate(win,xpos, ypos);
            return;
        }
    }

    else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_MIDDLE && mouseEvent.Pressed == 0)
    {
        //TODO : Not sure if widgets needs this event
        
        MiddMouseDRAGrelease(win, xpos, ypos);

        if (WidgWindow->handle(FR::FR_RELEASE) == 0) //Mouse click 
            m_GLFWevents = { -1,-1,-1,-1,-1 };

        mouseEvent.Old_x = mouseEvent.Old_y = 0;
        mouseEvent.Button = -1;
        return;
    }
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
    userData_ data;
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameraList[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    activeCamera->getUserData(data);

    if (mouseEvent.Old_x == 0 || mouseEvent.Old_y == 0) {
        //avoid having a jump and just make the delta = 0
        mouseEvent.Old_x = xpos ;
        mouseEvent.Old_y = ypos ;
        radiusXYZ = sqrt(data.camPosition_.x * data.camPosition_.x +
        data.camPosition_.y * data.camPosition_.y +
        data.camPosition_.z * data.camPosition_.z);
    }

    double deltax = mouseEvent.Old_x - xpos;
    double deltay = mouseEvent.Old_y - ypos;

    float xoffset = deltax * mouseDefaults.MouseXYScale  ;
    float yoffset = deltay * mouseDefaults.MouseXYScale  ;  //should we do this?

     data.camPosition_.x += xoffset;
     data.camPosition_.y += yoffset;

     data.direction_.x += xoffset ;
     data.direction_.y += yoffset;
 
    activeCamera->setUserData(data);
    mouseEvent.Old_x = xpos;
    mouseEvent.Old_y = ypos;
}
 
void Fr_GL3Window::cameraRotate(GLFWwindow* win, double xpos, double ypos)
{
    userData_ data;
    auto activeCamera = Fr_GL3Window::getfr_Gl3Window()->cameraList[(unsigned int)Fr_GL3Window::getfr_Gl3Window()->active_camera_];
    activeCamera->getUserData(data);
    ImVec4 viewPortDim = getPortViewDimensions();
    ImVec2 center = ImVec2((viewPortDim.z ) / 2, (viewPortDim.w )/ 2);
    int sign = 1;

    if (mouseEvent.Old_x == 0 && mouseEvent.Old_y == 0)
    {
        mouseEvent.Old_x = xpos;
        mouseEvent.Old_y = ypos;
        radiusXYZ = sqrt(data.camPosition_.x * data.camPosition_.x +
            data.camPosition_.y * data.camPosition_.y +
            data.camPosition_.z * data.camPosition_.z);
    }

    /*
        1         +        2
                  +      
    ---------------------------
        3         +        4
                  +
   */
    float deltax= mouseEvent.Old_x - xpos;
    float deltay = mouseEvent.Old_y - ypos;
    //if (deltax < 0 || deltay < 0)
    //    sign = -1;
    //else
    //    sign = 1;
    
    float tempAn = sign*glm::degrees(std::atan2(xpos, ypos));
   
    if (xpos < center.x && ypos < center.y) {       //1  270-360
        //lower0 part - right side
        phi = 270 + tempAn;
        FRTK_CORE_INFO(1);
    }else 

    if (xpos > center.x && ypos < center.y) {       //2 180-270
      //lower part - left side
        phi = 270 + tempAn;
        FRTK_CORE_INFO(2);
    }else

    if (xpos < center.x && ypos > center.y) {       //3 90-180
      //upper part - left side
        phi = 90 + tempAn;
        FRTK_CORE_INFO(3);
    }else
    if (xpos > center.x && ypos > center.y) {       //4  0 -90
      //upper part -  side
        phi = tempAn;
        FRTK_CORE_INFO(4);
    }
   // std::cout << "temphi " << tempAn <<"phi " << phi<<std::endl;
    std::cout << "centerx " << center.x <<"centery " << center.y << std::endl;

    data.camPosition_.x = radiusXYZ   * cos(glm::radians(phi));
    data.camPosition_.y = radiusXYZ  * sin(glm::radians(phi));
   // data.camPosition_.z = radiusXYZ * cos(glm::radians(theta));

    activeCamera->setUserData(data);
    mouseEvent.Old_x = xpos ;
    mouseEvent.Old_y = ypos ;
}

glm::vec3 Fr_GL3Window::computeSphereCoordinates(double x, double y, bool invertX_, bool invertY_ ) {
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    const float w = vp[2];
    const float h = vp[3];

    if (invertX_) 
        x = w - x;
    if (invertY_) 
        y = h - y;

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

void Fr_GL3Window::LeftMouseClick(GLFWwindow* win)
{

}

void Fr_GL3Window::RightMouseClick(GLFWwindow* win)
{
}


void Fr_GL3Window::MiddMouseClick(GLFWwindow* win)
{

}

void Fr_GL3Window::LeftMouseRelease(GLFWwindow* win)
{

}

void Fr_GL3Window::RightMouseRelease(GLFWwindow* win)
{
}


void Fr_GL3Window::MiddMouseRelease(GLFWwindow* win)
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

void Fr_GL3Window::LeftMouseDRAGrelease(GLFWwindow* win, double xoffset, double yoffset)
{
}

void Fr_GL3Window::RightMouseDRAGrelease(GLFWwindow* win, double xoffset, double yoffset)
{
}


void Fr_GL3Window::MiddMouseDRAGrelease(GLFWwindow* win, double xoffset, double yoffset)
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