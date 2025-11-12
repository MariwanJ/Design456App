//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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
#ifndef FR_WINDOW_H
#define FR_WINDOW_H

//#include <fr_ImGuiLayer.h>
//#include <fr_grid.h>
//#include<fr_axis3D.h>
#include<fr_scene.h>
#include <fr_boundbox.h>
#include <fr_core.h>
#if 1
#include <fr_transform.h>       //just for debug - remove it when done TODO : FIXME
#include <fr_camera.h>


#endif
/** Fr_Window */

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<../src/halfedge/fr_shape.h>

//fonts for Imgui icons
#include <imguiFont/IconsFontAwesome6.h>
 
#include <fr_filebrowser.h>
#include <widget/fr_line_widget.h>  //TODO: Put me somewhere else
#include <widget/fr_face_widget.h>  //TODO: Put me somewhere else

#include<fr_checkIntersection.h>

/** end Fr_Window */
namespace FR {
    //Change these as needed
    typedef struct {
        double Old_x ;  //SAVE X AND Y OF LAST Cursor Move
        double Old_y ;
        glm::vec3 WorldMouse;  
        int click ;
        int double_click;
        bool Pressed ;
        int Button;
    }glfwMouseEvent;


 
    typedef struct  {
        float MouseXYScale;
        float MouseScrollScale;
    }mouseScale_t;



    /**
     * Each of these variables will keep the last events happened and their value.
     * If the event is not relative to the variable, it will have -1 sa value.
     */
    struct eventData {
        int lastAction;
        int lastKey;
        int lastMod;
        int button;
        int scancode;
    };
    typedef eventData eventData_t;
    /** end of Fr_Window */

    FRTK_API class  Fr_Window {
        /** from Fr_Window */
    public:
        /**
         * Class constructor for main dummy window object that holds the FR_WIDGET system objects and their properties.
         */

        Fr_Window(int x, int y, int w, int h, std::string label);

        Fr_Window();
 
        /**
         * Class destructor.
         */
        ~Fr_Window();

        static Fr_Window* getFr_Window(void);
 
        void RenderGizmo(void);

        virtual int Exit();
        /**
         * Return back a pointer to the current GLFW window.
         *
         * \return pointer to a GLFW Window
         */
        static GLFWwindow* getCurrentGLWindow();

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
         * Create Sun (<Fr_Light>) inside the Scene graph.
         *
         * \return
         */

         /**
          * Resize Fr_Window size which affects glfw windows.
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

        virtual int GLFWrun();

        glm::vec3 calculateMouseRay();

        glm::vec3 toWorldCoords(const glm::vec4& eyeCoords);

        glm::vec4 toEyeCoords(const glm::vec4& clipCoords);

        glm::vec2 getNormalisedDeviceCoordinates(); 

        glm::vec3 getPointOnRay(const glm::vec3& ray, float distance);
        //experemental code 
        glm::vec3 calculateMouseWorldPos();

        //Mouse picker
        bool intersectionChecker(const ray_t& ray, glm::vec3& intersectionPoint);

        /**
         * Function to change the initialization variable of glad to false.
         * The variable will be used to avoid calling glad functions
         * while it is not initialized.
         */
        static void deinitializeGlad();
        GLFWcursor* MainWinCursor;  //needed to change to hand, rotation.

        int  x()const;
        int  y()const;
        int  w()const;
        int  h()const;

        const char* label()const;
        void label(std::string l);
        void label(const char* l);

        
        float getAspectRation() const;
        eventData_t GLFWevents() const;

        glfwMouseEvent getMouseEvents();

        void calculateScreenRay();

        /**
         * Handle is a very important function that take care of all events happining (mouse, keyboard or between widgets).
         * Whenever a widget consumes the events, it should return 0. FR_NO_EVENTS means that there is no more events left.
         * But if a widget uses the event but want to return the event to the system, it should return Fr_WGroup::handle(e).
         * or if the widget didn't care about the event, it should also return either 1 or Fr_WGroup::handle(e).
         *
         * \param events
         * \return
         */
        virtual int handle(int events);

        /**
         * Sets the camera
         * Returns true if the camera has been set
         * Returns the camera info by reference
         */
        virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

        /**
         * Sets the lights
         * Returns the light info by reference
         */
        virtual void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights);

        /**
         * Renders the node
         */
        virtual void Render(RenderInfo& info);

        void setCameraType(uint8_t typOfCamera);
        uint8_t getCameraType();
        
        static screenDim_t getScreenDim(void);

        int renderimGUI(userData_& data);
    
        static Fr_Window* spWindow;  //Row pointer otherwise we will not be able to set
        std::shared_ptr<Fr_Scene> activeScene;

        ImVec4 clear_color;



    protected:
        
  

        int imgui_LeftPanel();
        int imgui_ToolbarPannel();

        int imgui_ViewPort();
        int imgui_menu();

        int createGLFWwindow();

        int imguimzo_init();

        static glfwMouseEvent mouseEvent;
        
        static screenDim_t m_ViewPort;

        GLFWcursor* cursorHand = nullptr;
        GLFWcursor* cursorCrosshair = nullptr;

        static void glfwWindosResize(GLFWwindow* window, int width, int height);
        static void glfwWindPos(GLFWwindow* window, int pos_x, int pos_y);

      

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void cursor_m_positioncallback(GLFWwindow* win, double xpos, double ypos);

        static void cursor_enter_callback(GLFWwindow* win, int entered);

        static void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);

        static void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);

        static void MouseMovement(double xoffset, double yoffset);

        static void cameraPAN(GLFWwindow* win, double xoffset, double yoffset);

        static void cameraRotate(GLFWwindow* win, double xoffset, double yoffset);

        static void joystick_callback(int jid, int events);
  
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

        void mnuDrawLine_cb(void* Data);

        void createOpenDialog(void);
        /**
         * GLAD VERSION DEFINITION
         * Currently it is 4.3.
         */
    private:
        int gl_version_major;
        int gl_version_minor;
        mouseScale_t mouseDefaults;

        static eventData m_GLFWevents;        //All GLFW events that will be used by FR_WIDGET system

        //Mouse picker variable
        static int RECURSION_COUNT;
        static float RAY_RANGE;

   

        void flush();
       
        /**
         * Boolean variable keeps information about GLFW window if it is initialized or not.
         */
        static bool s_GLFWInitialized;
        /**
         * Boolean variable to know if GLAD is initialized or not.
         */
        static bool s_GladInitialized;
        std::string m_label;
        /**
         * Keep track of the active camera.
         */

        
        std::shared_ptr<ImGui::FileBrowser> fileDialog;

        bool showOpenDialog;
        //will be true if rotate/pan starts.
        static bool MouseOnce;
        static float m_MousePickerRadius;
        static float phi, theta;

        //Camera rotation - mouse callback
        float radiusXYZ;
        bool runCode;

        static GLFWwindow* pGLFWWindow;

    };
}

#endif // !FR_WINDOW_H
