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
//#include<Fr_Core.h>
#include<Scene.h>
#include<Camera.h>
#include<Manipulator.h>
//#include<Transform.h>
#include<Light.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Grid.h>


/* Cameras */
class Camera;


//Camera struct which will keep the camera and a manipulator for the camera
 
class Fr_GL3Window;

class FRTK_API Fr_GL3Window : public Fl_Window {
public:
    //class constructors
    Fr_GL3Window(int x, int y, int w, int h, const char* l);
   
    virtual ~Fr_GL3Window();
    virtual int exit();
    Fl_Window* pfltkWindow;
    int embeddGLfwWindow();
    int releaseGLfwWindow();
    virtual GLFWwindow* getCurrentGLWindow();
    virtual void reset(void);

    virtual void resizeGlWindow(float ratio);
    virtual void resizeGlWindow(int x, int y, int w, int h);
    void setOpenGLWinowSize(int xGL, int yGL, int wGL, int hGL);


    virtual void CreateScene();  //Must be overriden to get the desired results
    virtual std::shared_ptr<Transform> CreateSun();

    void resize(int x, int y, int w, int h);
    void resizable(Fl_Widget* w);
    virtual void draw();           //fltk
    virtual void show();           //both
    virtual void gladEvents(int events);    //
    virtual int handle(int event); //FLTK handle
    virtual int glfw_handle(int evenet); //Take care of GLFW events
    virtual void hide();
    virtual int GLFWrun();

    static float fltktimerValue;
    static double oldTime;
    static double newTime;

    static Scene* scene;
    std::vector<std::shared_ptr<Transform>> cameras; //PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT, 
    //std::shared_ptr<Camera> camera;
    Manipulator *manipulator;
    static GLFWwindow* pWindow;
    static void deinitializeGlad();
protected:
    void CreateCameras();
    int createGLFWwindow();
    int updateGLFWWindow();


private:
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
    void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
    void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
    void scroll_callback(GLFWwindow*, double xoffset, double yoffset);
    void joystick_callback(int jid, int events);


    class GLFWCallbackWrapper
    {
    public:
        GLFWCallbackWrapper() = delete;
        GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
        GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
        ~GLFWCallbackWrapper() = delete;

        //These are for avoiding error when you call non static functions.
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
        static void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
        static void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
        static void scroll_callback(GLFWwindow*, double xoffset, double yoffset);
        static void joystick_callback(int jid, int events);
        static void setGLFWwindow(Fr_GL3Window* glfwWindow);
    private:
        static  Fr_GL3Window* s_fr_glfwwindow;
    };



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
    
    Transform *sun;

    HWND glfwHND;
    static bool s_GLFWInitialized;
    static bool s_GladInitialized;
    static int _xGl; // It is different than FLTK. But it is depends on  x()
    static int _yGl; // It is different than FLTK. But it is depends on  y()
    static int _wGl; // It is different than FLTK. But it is depends on  w()
    static int _hGl; // It is different than FLTK. But it is depends on h()
    CameraList active_camera_ ;
    const int Ox, Oy, Ow, Oh; //origional vlaues. 
};

#endif