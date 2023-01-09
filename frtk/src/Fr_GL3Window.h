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
#include<fr_widgets/fr_basic_shapes.h>

class Fr_GL3Window;

//callbacks - private
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
void scroll_callback(GLFWwindow*, double xoffset, double yoffset);

class FRTK_API Fr_GL3Window : public Fl_Double_Window {
public:
    Fr_GL3Window(int x, int y, int w, int h, const char* l);
    Fr_GL3Window(int x, int y, int w, int h);
    Fr_GL3Window(int w, int h, const char* l);
    Fr_GL3Window(int w, int h);
    virtual ~Fr_GL3Window();
    virtual int exit();
    Fl_Double_Window* pfltkWindow;
    int embeddGLfwWindow();
    virtual void reset(void);
    virtual void resizeGlWindow(int x, int y, int w, int h);
    void resize(int x, int y, int w, int h);
    void resizable(Fl_Widget* w);
    virtual void draw();           //fltk
    virtual void show();           //both
    virtual void gladEvents(int events);    //
    virtual int handle(int event); //FLTK handle
    virtual int glfw_handle(int evenet); //Take care of GLFW events
    virtual void hide();
    int GLFWrun();
    static void redrawFLTKTimer_cb(void*window);

protected:
    int createGLFWwindow();
    int updateGLFWWindow();
    unsigned int VBO, VAO;
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
    static void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
    static void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
    static void scroll_callback(GLFWwindow*, double xoffset, double yoffset);

    bool overlay;
    void setOverlay();
    void removeOverlya();

    GLuint shaderProgram;
    GLuint vertexArrayObject;
    GLuint vertexBuffer;
    GLint positionUniform;
    GLint colourAttribute;
    GLint positionAttribute;

    int gl_version_major;
    int gl_version_minor;
    void flush();
    static GLFWwindow* pWindow;

    HWND glfwHND;
    static bool s_GLFWInitialized;
    static bool s_GladInitialized;
    static int _xGl; // It is different than FLTK. But it is depends on  x()
    static int _yGl; // It is different than FLTK. But it is depends on  y()
    static int _wGl; // It is different than FLTK. But it is depends on  w()
    static int _hGl; // It is different than FLTK. But it is depends on h()
};

#endif