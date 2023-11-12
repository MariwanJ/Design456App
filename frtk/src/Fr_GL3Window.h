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

#include<fr_scene.h>
#include<fr_camera.h>
#include<fr_light.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fr_grid.h>
#include<fr_axis3D.h>
#include<fr_texture_buffer.h>  //used to render to texture - imgui
#include<../src/halfedge/fr_new_mesh.h>
//fonts for Imgui icons
#include <imguiFont/IconsFontAwesome6.h>
#include <fr_ImGuiLayer.h>
#include <fr_filebrowser.h>
#define MAX_CAMERAS 8  //JUST FOR CLARIFICATION - SHOULD NOT BE CHANGE WITHOUT CHAINING CameraList enu

/* Cameras */
class Camera;
class Fr_GL3Window;

/**
 *  Fr_GL3Windows class definition and methods.
 */
class FRTK_API Fr_GL3Window {
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
    Fr_GL3Window(int x, int y, int w, int h, std::string l);
    /**
     *
     * Default constructor.
     *
     */
    Fr_GL3Window();
    /**
    * Class destructor.
    *
    */

    static Fr_GL3Window* getfr_Gl3Window();

    virtual ~Fr_GL3Window();
    /**
     * Exit function used to exit
     *
     * \return int value depending on the way the windows exits.
     */

     /**
      * Add imgui layer to current view port
      * @param layer : shared pointer to Fr_ImGuiLyer object
     */
    virtual void addLayer(std::shared_ptr<Fr_ImGuiLayer> layer);
    virtual void removeLayer(std::shared_ptr<Fr_ImGuiLayer> layers);

    virtual int Exit();
    /**
     * Return back a pointer to the current GLFW window.
     *
     * \return pointer to a GLFW Window
     */
    virtual GLFWwindow* getCurrentGLWindow();

    /**
     * Resize and move the GLFWWindow by the parameters given.
     *
     * \param x  left position ref to the screen
     * \param y  top position ref to the screen
     * \param w  width of the screen
     * \param h  height of the screen
     */
    virtual void resizeWindow(int x, int y, int w, int h);

    /**
     * Create Scene graph.
     */
    virtual void CreateScene();  //Must be overridden to get the desired results
    /**
     * Create Sun (Light) inside the Scene graph.
     *
     * \return
     */
    virtual std::shared_ptr<Transform> CreateSunTop();
    virtual std::shared_ptr<Transform> CreateSunBottom();  //TODO: NOT SURE IF WE NEED 2?? 

    /**
     * Resize Fr_GL3Window size which affects glfw windows.
     *
     * \param x left-start position of the window
     * \param y top-start position of the window
     * \param w width of the window
     * \param h height of the window
     */
    virtual void resize(int x, int y, int w, int h);
    /**
     * Show the window. This will also create different objects - See implementation
     */
    virtual void show();           //both

    /**
     * Hide the window which
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

public:
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
    std::vector<std::shared_ptr<Camera>> cameraList; //PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT,

    /**
     * Static pointer used to access the GLFW window.
     */
    GLFWwindow* pWindow;
    /**
     * Function to change the initialization variable of glad to false.
     * The variable will be used to avoid calling glad functions
     * while it is not initialized.
     */
    static void deinitializeGlad();

    std::shared_ptr<Fr_TextureFrameBuffer> sceneBuffer;

    int  x()const;
    int  y()const;
    int  w()const;
    int  h()const;

    ImVec4 getPortViewDimensions();
    void setPortViewDimension(ImVec4 value);

    const char* label()const;
    void label(std::string l);
    void label(const char* l);

    void setCameraType(CameraList typOfCamera);
    CameraList getCameraType();
    int imgui_CameraConfiguration(userData_& data);
    genID idGen_; //Keeps the id generator - used to generate shape/objects unique ID
    float getAspectRation() const;
protected:
    /**
     * Function to create all cameras listed in CameraList.
     *
     */
    void CreateCameras();

    /**
     *
     * Collect all Rendering functions under one function for simplifying the work.
     *
     * \return
     */
    int renderimGUI(userData_& data);
    int imgui_LeftPanel();
    int imgui_TopPannel();

    int imgui_ViewPort();
    int imgui_menu();

    /**
     * Create the GLFW Window .
     *
     * \return
     */
    int createGLFWwindow();

    int imguimzo_init();

private:

    /** GLFW Callbacks*/
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursor_position_callback(GLFWwindow*, double xpos, double ypos);
    void cursor_enter_callback(GLFWwindow*, int entered); //      GL_TRUE if the cursor entered the window's client area, or GL_FALSE if it left it.
    void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
    void scroll_callback(GLFWwindow*, double xoffset, double yoffset);

    void cameraPAN(double xoffset, double yoffset);
    void cameraRotate(double xoffset, double yoffset);

    void LeftMouseClick(double xoffset, double yoffset);
    void RightMouseClick(double xoffset, double yoffset);

    void joystick_callback(int jid, int events);

    //Menu and toolbar callbacks
    void mnuFileNew_cb(void* Data);
    void mnuFileOpen_cb(void* Data);
    void mnuFileClose_cb(void* Data);
    void mnuFileSave_cb(void* Data);
    void mnuFileSaveAs_cb(void* Data);
    void mnuFileExport_cb(void* Data);
    void mnuFileImport_cb(void* Data);
    void mnuFileExit_cb(void* Data);
    void CameraOptions(void);
    void SunOptions(void);

    void mnuEditUndo(void* Data);
    void mnuEditRedo(void* Data);
    void mnuEditCopy(void* Data);
    void mnuEditCut(void* Data);
    void mnuEditPaste(void* Data);

    void createOpenDialog(void);

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

        //Menu callback rappers
        static void mnuFileNew_cb(void* Data);
        static void mnuFileOpen_cb(void* Data);
        static void mnuFileClose_cb(void* Data);
        static void mnuFileSave_cb(void* Data);
        static void mnuFileSaveAs_cb(void* Data);
        static void mnuFileExport_cb(void* Data);
        static void mnuFileImport_cb(void* Data);
        static void mnuFileExit_cb(void* Data);

        static void GLFWCallbackWrapper::mnuEditUndo(void* Data);
        static void GLFWCallbackWrapper::mnuEditRedo(void* Data);
        static void GLFWCallbackWrapper::mnuEditCopy(void* Data);
        static void GLFWCallbackWrapper::mnuEditCut(void* Data);
        static void GLFWCallbackWrapper::mnuEditPaste(void* Data);

    private:
        static  Fr_GL3Window* s_fr_glfwwindow;
    };

    /**
     * GLAD VERSION DEFINITION
     * Currently it is 4.3.
     */
private:
    int gl_version_major;
    int gl_version_minor;

    //Keep ImGui layers saved and removed
    std::vector<std::shared_ptr<Fr_ImGuiLayer>> layers_;

    void flush();

    /**
     * Transform pointer used to keep track to the scene graph SUN
     * .
     */
    std::shared_ptr<Light> sun;
    std::shared_ptr<Transform> sunT;
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
    int _x;
    int _y;
    int _w;
    int _h;
    std::string label_;
    /**
     * Keep track of the active camera.
     */
    CameraList active_camera_;
    ImVec4 clear_color;
    static Fr_GL3Window* s_Fr_GLFWwindow;
    ImGui::FileBrowser fileDialog;

    bool showOpenDialog;
    //will be true if rotate/pan starts.
    static bool MouseOnce;
    float yaw, pitch, roll;

    //Camera rotation - mouse callback
    float radiusXYZ;

    ImVec4 PortViewDimensions;

#if 1//Experemental code - will be removed
    std::shared_ptr <Transform> tempBu;
#endif
};

#endif