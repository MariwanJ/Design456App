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


#ifndef FR_GL3WINDOW_H
#define FR_GL3WINDOW_H

#include <frtk.h>
#include<Fr_Core.h>
#include<Scene.h>
#include<Camera.h>
#include<Manipulator.h>
#include<Transform.h>
#include<Light.h>
#include <glm/gtc/matrix_transform.hpp>
/* 
and manipulators */

class Camera;
enum CameraList {
    Cam1,
    Cam2,
    Cam3,
    Cam4
};

typedef struct {
    Camera* camera;
    Manipulator* manipulator;
 } cam;
 

static int curr_camera = Cam1;

class Fr_GL3Window;

//callbacks - private
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//
//void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
//void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
//void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
//void scroll_callback(GLFWwindow*, double xoffset, double yoffset);

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
    int releaseGLfwWindow();

    virtual void reset(void);
    virtual void resizeGlWindow(int x, int y, int w, int h);
    virtual void CreateScene();
    virtual std::shared_ptr<Camera> CreateCamera(Group* parent, int cameraId);
    virtual std::shared_ptr<Transform> CreateSun();
    
       void resize(int x, int y, int w, int h);
    void resizable(Fl_Widget* w);
    virtual void draw();           //fltk
    virtual void show();           //both
    virtual void gladEvents(int events);    //
    virtual int handle(int event); //FLTK handle
    virtual int glfw_handle(int evenet); //Take care of GLFW events
    virtual void hide();
    int GLFWrun();
    //static void redrawFLTKTimer_cb(void*window);
    static float fltktimerValue;
    static double oldTime;
    static double newTime;
    void setOpenGLWinowSize(int xGL, int yGL, int wGL, int hGL);

    static Scene* scene;
    std::vector<cam> cameras;
    std::shared_ptr<Camera> camera;
    Manipulator *manipulator;


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
    
    Transform *sun;

    HWND glfwHND;
    static bool s_GLFWInitialized;
    static bool s_GladInitialized;
    static int _xGl; // It is different than FLTK. But it is depends on  x()
    static int _yGl; // It is different than FLTK. But it is depends on  y()
    static int _wGl; // It is different than FLTK. But it is depends on  w()
    static int _hGl; // It is different than FLTK. But it is depends on h()
    int curr_camera ;

};

#endif