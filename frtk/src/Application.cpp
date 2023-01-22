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



#include<Fr_Core.h>
#include<Fr_GL3Window.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Scene.h>
//#include <Camera.h>
//#include <Engine.h>
//#include <Light.h>
//#include <Manipulator.h>
//#include <Mesh.h>
//#include <Scene.h>
//#include <ToonShaderNode.h>
//#include <Transform.h>




 /* Scene and engine*/
static Scene *scene = nullptr;


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
        int state = 0; //TODO FIXME DONT KNOW WHAT TO WRITE
        int button=-1;
        if (FR::glfw_MouseButton==GLFW_MOUSE_BUTTON_LEFT)
            button= 0;//TODO FIDME 
        else if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT)
            button = 1;//TODO FIDME 
        
            double cposx, cposy;
            glfwGetCursorPos(win, &cposx, &cposy);
            FR::glfw_e_x = cposx;
            FR::glfw_e_y = cposy;
            if (button ==0 || button ==1)
                if (win != nullptr) {
                    std::cout << cposx << " " << cposy << std::endl;
                    FR::globalP_pWindow->cameras[FR::globalP_pWindow->curr_camera].manipulator->GLFWMouse(button, state, cposx, cposy);
                   // FR::globalP_pWindow->updateGLFWWindow();
                  //  glfwSwapBuffers(win);
                    FR::globalP_pWindow->scene->RenderScene();
        }
    
}

void Fr_GL3Window::cursor_enter_callback(GLFWwindow*, int entered)
{
}

void Fr_GL3Window::mouse_button_callback(GLFWwindow*win, int button, int action, int mods)
{
    FR::glfw_MouseButton = button;
}

void Fr_GL3Window::scroll_callback(GLFWwindow*, double xoffset, double yoffset)
{
}



int FakeMain(int argc, char* argv[]) {
    Fr_GL3Window* win = new Fr_GL3Window(0, 0, 1000, 800, "Modern OpenGL with FLTK support");
    win->setOpenGLWinowSize(70, 60, 900, 700);
    win->resizable(win);
    //win->resizable(win);
//Fl_Button* b1 = new Fl_Button(10, 5, 50, 40, "Release");
//Fl_Button* b2 = new Fl_Button(100, 5, 50, 40, "CHILD");


    win->show();
    win->GLFWrun();
    return 0; 
}

