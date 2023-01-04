/*                                                                      *
 This file is a part of the Open Source Design456App                    *
                                                                        *
 Copyright (C) 2023                                                     *
                                                                        *
 This library is free software; you can redistribute it and/or          *
 modify it under the terms of the GNU Lesser General Public             *
 License as published by the Free Software Foundation; either           *
 version 2 of the License, or (at your option) any later version.       *
                                                                *
 This library is distributed in the hope that it will be useful,        *
 but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 Lesser General Public License for more details.                        *
                                                                *
 You should have received a copy of the GNU Lesser General Public       *
 License along with this library; if not, If not, see                   *
 <http://www.gnu.org/licenses/>										*
 .																*
 Author :Mariwan Jalal    mariwan.jalal@gmail.com                       *
*/

#ifndef FR_GL3WINDOW_H
#define FR_GL3WINDOW_H
#include <frtk.h>
#include<Fr_Core.h>

class Fr_GL3Window;

//callbacks - private
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
void scroll_callback(GLFWwindow*, double xoffset, double yoffset);

int Fr_GL3Window::_xGl=0;
int Fr_GL3Window::_yGl=0;
int Fr_GL3Window::_wGl=0;

static int _hGl; // It is different than FLTK. But it is depends on h()
class FRTK_API Fr_GL3Window : public Fl_Window {
public:
    Fr_GL3Window(int x, int y, int w, int h, const char* l);
    Fr_GL3Window(int x, int y, int w, int h);
    Fr_GL3Window(int w, int h, const char* l);
    Fr_GL3Window(int w, int h);
    virtual ~Fr_GL3Window();

    virtual void reset(void);
    virtual void resizeGlWindow(int x, int y, int w, int h);
    void resize(int x, int y, int w, int h) override;

    virtual void draw() override;           //fltk
    virtual void redraw();                  //both
    virtual void show() override;           //both
    virtual void gladEvents(int events);    //
    virtual int handle(int event) override; //FLTK handle
    virtual int glfw_handle(int evenet); //Take care of GLFW events

protected:
    int createGLFWwindow();
    int updateGLFWWindow();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
    static void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
    static void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
    static void scroll_callback(GLFWwindow*, double xoffset, double yoffset);


    bool overlay;
    //Let FLTK draw over GLFW
    void setOverlay();
    /* Don't draw over GLFW -
    Warning the object will still try to draw but
    it will not be visible */
    void removeOverlya();

    GLuint shaderProgram;
    GLuint vertexArrayObject;
    GLuint vertexBuffer;
    GLint positionUniform;
    GLint colourAttribute;
    GLint positionAttribute;

    int gl_version_major;
    int gl_version_minor;

    static GLFWwindow* pWindow;
    static Fl_Window* FlglWindow;

    HWND glfwHND;
    static bool s_GLFWInitialized;
    static bool s_GladInitialized;

    static int _xGl; // It is different than FLTK. But it is depends on  x()
    static int _yGl; // It is different than FLTK. But it is depends on  y()
    static int _wGl; // It is different than FLTK. But it is depends on  w()
    static int _hGl; // It is different than FLTK. But it is depends on h()
};

#endif