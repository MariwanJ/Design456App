//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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

#include <fr_core.h>
#include<fr_scene.h>
#include <fr_boundbox.h>
#include <fr_transform.h>       //just for debug - remove it when done TODO : FIXME
#include <fr_camera.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<../src/halfedge/fr_shape.h>
#include <mesh_widget/fr_line_widget.h>  //TODO: Put me somewhere else
#include <mesh_widget/fr_face_widget.h>  //TODO: Put me somewhere else

#include<fr_checkIntersection.h>



/** end Fr_Window */
namespace FR {
    class Frtk_Window;
    
    class Frtk_ToolBarWin;
    class Frtk_Radio_ToolbarWin;

    FRTK_API class  Fr_Window {
        friend Frtk_Window;
    public:
        virtual ~Fr_Window();
        // Singleton accessor
        static std::shared_ptr<Fr_Window> getFr_Window(
            int x = 0, int y = 0, int w = 800, int h = 600, const std::string& label = "Design456App");
        
    protected:
        Fr_Window(int x, int y, int w, int h, const std::string& label);

    public:
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
          * Resize Fr_Window size which affects glfw windows.
          *
          * \param x left-start position of the window
          * \param y top-start position of the window
          * \param w width of the window
          * \param h height of the window
          */
        virtual void resize(int x, int y, int w, int h);

        virtual void show();
        virtual void hide();

        virtual int GLFWrun();

        glm::vec3 calculateMouseRay();

        glm::vec3 toWorldCoords(const glm::vec4& eyeCoords);

        glm::vec4 toEyeCoords(const glm::vec4& clipCoords);

        glm::vec2 getNormalisedDeviceCoordinates();

        glm::vec3 getPointOnRay(const glm::vec3& ray, float distance);
        //experimental code
        glm::vec3 calculateMouseWorldPos();


        

        /**
         * Function to change the initialization variable of glad to false.
         * The variable will be used to avoid calling glad functions
         * while it is not initialized.
         */
        static void deinitializeGlad();


        int  x()const;
        int  y()const;
        int  w()const;
        int  h()const;

        const char* label()const;
        void label(std::string& l);
        void label(const char* l);

        static float m_MousePickerRadius;

        float getAspectRation() const;
        void calculateScreenRay();

        NVGcontext* getnvgContext(void); //NanoVG Context
        
        /**
         * Handle is a very important function that take care of all events happening (mouse, keyboard or between widgets).
         * Whenever a widget consumes the events, it should return 0. FR_NO_EVENTS means that there is no more events left.
         * But if a widget uses the event but want to return the event to the system, it should return Fr_WGroup::handle(e).
         * or if the widget didn't care about the event, it should also return either 1 or Fr_WGroup::handle(e).
         *
         * \param events
         * \return
         */
        virtual int handle(int events);


        //Treats events per frame 
        virtual void updateInputEvents(void);

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

        int renderimGUI(userData_t& data);

        int renderNewGUI(); //temporary function 


        static Fr_InputEvent_t m_sysEvents;
        void initSystemEvents();
        void deactivateNavi();
        void activateNavi();

        float menuHeight(void) const;
        
		defaultFont SystemFont;
        static std::shared_ptr<Fr_Window> spWindow;

        std::vector<std::shared_ptr<Frtk_Window>> m_frtkWindow;

        std::shared_ptr<Fr_Scene> activeScene;

        ImVec4 clear_color;

        GLFWcursor* MainWinCursor;  //needed to change to hand, rotation.
        std::vector<CharEvent_t> m_unicodeChars;

    protected:

        std::shared_ptr<Frtk_ToolBarWin>  createMainToolbar();
        std::shared_ptr<Frtk_ToolBarWin> createSelectionToolbar();
        std::shared_ptr<Frtk_ToolBarWin> m_MainToolbar;
        std::shared_ptr<Frtk_ToolBarWin> m_selectionTB;

        FRTK_WIN_TYPE m_winType;
        static screenDim_t m_ViewPort;

        GLFWcursor* cursorHand = nullptr;
        GLFWcursor* cursorCrosshair = nullptr;


        void mainToolbar_callback(size_t index, void *data=nullptr);
        void selectionToolbar_callback(size_t index, void *data=nullptr);

        int imgui_LeftPanel();
        int imgui_menu();

        int createGLFWwindow();

  

        int imguimzo_init();


        static void glfwWindosResize(GLFWwindow* window, int width, int height);
        static void glfwWindPos(GLFWwindow* window, int pos_x, int pos_y);

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void char_callback(GLFWwindow* window, unsigned int codepoint);
        
        static void cursor_m_positioncallback(GLFWwindow* win, double xpos, double ypos);

        static void cursor_enter_callback(GLFWwindow* win, int entered);

        static void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);

        static void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);

        static void cameraPAN(GLFWwindow* win);

        static void cameraRotate(GLFWwindow* win);
        void cameraZoom(GLFWwindow* win);

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

        //Selection toolbar callbacks
        void mnuSelMesh_cb(void* data);
        void mnuSelFace_cb(void* data);
        void mnuSelEdges_cb(void* data);
        void mnuSelVertex_cb(void* data);

        void CameraOptions(void);
        void SunOptions(void);

        void mnuEditUndo(void* Data);
        void mnuEditRedo(void* Data);
        void mnuEditCopy(void* Data);
        void mnuEditCut(void* Data);
        void mnuEditPaste(void* Data);

        void mnuDrawLine_cb(void* Data);

        /**
         * GLAD VERSION DEFINITION
         * Currently it is 4.3.
         */
    private:
        std::string m_label;
        float m_menuHeight;
        bool m_NaviCube;
        int gl_version_major;
        int gl_version_minor;
        mouseScale_t mouseDefaults;

        //Mouse picker variable
        static int RECURSION_COUNT;
        static float RAY_RANGE;
        static bool m_RotateActive;

        /**
         * Boolean variable keeps information about GLFW window if it is initialized or not.
         */
        static bool s_GLFWInitialized;
        /**
         * Boolean variable to know if GLAD is initialized or not.
         */
        static bool s_GladInitialized;

        /**
         * Keep track of the active camera.
         */
        //will be true if rotate/pan starts.
        static bool MouseOnce;

        static float phi, theta;

        //Camera rotation - mouse callback
        float radiusXYZ;
        bool runCode;

        static GLFWwindow* pGLFWWindow;
        NVGcontext* m_nvgContext; //NanoVG Context

        void flush();


    };
}

#endif // !FR_WINDOW_H
