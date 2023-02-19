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
//#include<fr_core.h>
#include<Scene.h>
#include<Camera.h>
#include<Manipulator.h>
//#include<Transform.h>
#include<Light.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fr_grid.h>
#include<fr_axis3D.h>
#include <FL/Fl_Window.H>
/* Cameras */
class Camera;


class Fr_GL3Window;

/**
 *  Fr_GL3Windows class definition and methods.
 */
class FRTK_API Fr_GL3Window : public Fl_Window {
public:
    /**
     * class constructors.
     * 
     * \param x left side of the window ref to the whole screen (System dependen)
     * \param y top side of the window ref to the whole screen (System dependen)
     * \param w width of the window (max depends on the rosolution of the screen)
     * \param h hight of the window (mad depends on the resolution of the screen)
     * \param l Windows title bar label
     */
    Fr_GL3Window(int x, int y, int w, int h, const char* l);
   /**
    * Class destructor.
    * 
    */
    virtual ~Fr_GL3Window();
    /**
     * Exit function used to exit whenever the fltk windows is closed.
     * 
     * \return int value dpending on the way the windows exits.
     */
    virtual int exit();
    /**
     * Pointer to the FLTK Window used to get different parameters using FLTK methods.
     */
    Fl_Window* pfltkWindow;
    /**
     * Function to let the GLFW windows becomes a child of FLTK window.
     * 
     * \return int value which represent the success/failure of the operation
     */
    int embeddGLfwWindow();
    /**
     * let GLFW window be seperated from the FLTK window and it wouln't be a child of the Fl_Window any more.
     * 
     * \return 
     */
    int releaseGLfwWindow();
    /**
     * Return back a pointer to the current GLFW window.
     * 
     * \return pointer to a GLFW Window
     */
    virtual GLFWwindow* getCurrentGLWindow();


    /**
     * Resize GLFW Window.
     * 
     * \param ratio represent the scale of the change (for ex by 1.1 scale)
     */
    virtual void resizeGlWindow(float ratio);
    /**
     * Resize and move the GLFWWindow by the parameters givven.
     * 
     * \param x  left position ref to the screen
     * \param y  top position ref to the screen
     * \param w  width of the screen
     * \param h  height of the screen
     */
    virtual void resizeGlWindow(int x, int y, int w, int h);
    /**
     * Initial setup for the GLFW widow dimension.
     * 
     * \param xGL left start point
     * \param yGL top start point
     * \param wGL width 
     * \param hGL height
     */
    void setOpenGLWinowSize(int xGL, int yGL, int wGL, int hGL);

    /**
     * Create Scene graph.
     */
    virtual void CreateScene();  //Must be overriden to get the desired results
    /**
     * Create Sun (Light) inside the Scene graph.
     * 
     * \return 
     */
    virtual std::shared_ptr<Transform> CreateSun();

    /**
     * Resize Fr_GL3Window size which affects both fltk and glfw windows.
     * 
     * \param x left-start position of the window
     * \param y top-start position of the window
     * \param w width of the window
     * \param h height of the window
     */
    virtual void resize(int x, int y, int w, int h);
    /**
     * Decides weather the windwo is resizable or not and which child will be also resizable (see FLTK for further info).
     * 
     * \param w
     */
    virtual void resizable(Fl_Widget* w);
    /**
     * Draw function for FLTK. This will draw the window and the childrens (only FLTK)
     */
    virtual void draw();           //fltk
    /**
     * Show the window. This will also create different objects - See implementation 
     */
    virtual void show();           //both
    /**
     * .
     */
    /**
     * Hanle function (See fltk for further info).
     * This is only related to FLTK- Glfw window has it's own callbacks
     */
    virtual int handle(int event); //FLTK handle
    /**
     * .
     */
    /**
     * Hide the window which also close it. both FLTK and GLFW
     * 
     */
    virtual void hide();

    /**
     * Windows run function wich replaces the Fl::run() function.
     * This is necessary to avoid problem with the Fl:run
     * 
     * \return int value which represents the windows exit code
     */
    virtual int GLFWrun();
    
    /**
     * These timer variables are used to decide the fps of updating the FLTK.
     * Since we are not using Fl:run, the update must be decided by GLFW render function. 
     * See the implementation
     */
    static float fltktimerValue;
    static double oldTime;
    static double newTime;

    /**
     * Pointer to link to the scene.
     */
    static Scene* scene;
    /**
     * Vecotor of shared pointers for Transform object.
     * Transform object will have only one child which is a camera
     * 6 types of cameras are created by the window
     * see CameraList
     */
    std::vector<std::shared_ptr<Transform>> cameras; //PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT, 
    /**
     * Static pointer used to access the GLFW window.
     */
    static GLFWwindow* pWindow;
    /**
     * Function to change the initialization variable of glad to false.
     * The variable will be used to avoid calling glad functions
     * while it is not initialized.
     */
    static void deinitializeGlad();

protected:
    /**
     * Function to create all cameras listed in CameraList.
     * 
     */
    void CreateCameras();
    /**
     * Create the GLFW Window and embedd it to fltk.
     * 
     * \return 
     */
    int createGLFWwindow();

    //TODO : Is it necessary or we can remove this??
    /**
     * Low level code to initialize the GLFW and make it a child object.
     * 
     * \return 
     */
    int updateGLFWWindow();

private:
   
    /** GLFW Callbacks*/
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
    void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
    void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
    void scroll_callback(GLFWwindow*, double xoffset, double yoffset);
    void joystick_callback(int jid, int events);

    /**
     * GLFW callback wrapper calss.
     * This class is necessary to avoid having static callback functions. 
     * This allow us to reach Fr_GL3Window variables without using 
     * other solutions. 
     */
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

    /**
     * boolean varialbe to allow fltk to draw on top of GLFW.
     * TODO: NOT IMPLEMENTED YET
     */
    bool overlay;
    /**
     * Sets the overlay variable to true .
     * 
     */
    void setOverlay();
    /**
     * sets the overlay variable to false .
     * 
     */
    void removeOverlya();
    
  /*/
    GLuint shaderProgram;
    GLuint vertexArrayObject;
    GLuint vertexBuffer;
    GLint positionUniform;
    GLint colourAttribute;
    GLint positionAttribute;
    */
    /**
     * GLAD VERSION DEFINITION
     * Currently it is 4.3.
     */
    int gl_version_major;
    int gl_version_minor;
    /**
     * Update immediatly both FLTK and GLFW windows.
     * see FLTK for further info
     */
    void flush();
    
    /**
     * Transform pointer used to keep track to the scene graph SUN.
     */
    Transform *sun;

    /**
    * low level variable to keep the id of the GLFW window
     * HWND .
     * TODO: Implement the Linxu and other OS 
     */
    HWND glfwHND;
    /**
     * Boolean variale keeps information about GLFW window if it is initialized or not.
     */
    static bool s_GLFWInitialized;
    /**
     * Boolean variable to know if GLAD is initialized or not.
     */
    static bool s_GladInitialized;
    /**
     * Private values that keep the dimention of the window.
     */
    static int _xGl; // It is different than FLTK. But it is depends on  x()
    static int _yGl; // It is different than FLTK. But it is depends on  y()
    static int _wGl; // It is different than FLTK. But it is depends on  w()
    static int _hGl; // It is different than FLTK. But it is depends on h()
    /**
     * Keep track of the active camera.
     */
    CameraList active_camera_ ;
    /**
     * Variables to keep old dimiention of the window to calculate the resizing ratio.
     */
    const int Ox, Oy, Ow, Oh; //origional vlaues. 
};

#endif