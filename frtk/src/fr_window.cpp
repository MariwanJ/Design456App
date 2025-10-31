#include "fr_window.h"
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

/**
 *
 * This object is a container for the FR_WIDGETS. It has important widget method, property and is their parent :
 * 1- Deliver events
 * 2- Keep track of widgets, add, remove,
 * 3- Layer responsible for the whole FR_WIDGET system (ONLY ONE LAYER AT THE MOMENT, THIS IS A DESIGN QUESTION THAT I DONT KNOW the answer)
 * .
 */
#include "fr_window.h"
#include "fr_widget.h"
 /** Fr_Window */

  //Remove me later : TODO
#include<halfedge/fr_shape.h>

#if 1 //experimental code TODO: REMOVE ME 
#include <fr_text.h>
#endif

/** end fr_grl3 */
namespace FR {



    









    /** from Fr_Window */
    int Fr_Window::RECURSION_COUNT = 200;
    float Fr_Window::RAY_RANGE = 600;
    GLuint m_QuadVA, m_QuadVB, m_QuadIB;

    bool Fr_Window::s_GLFWInitialized = false;
    bool Fr_Window::s_GladInitialized = false;
    float Fr_Window::m_MousePickerRadius = 5;        //FreeCAD uses 5 pixels as default
    float Fr_Window::phi = 0.0f;
    float Fr_Window::theta = 0.0f;

    Fr_Window* Fr_Window::spWindow = nullptr;
    eventData Fr_Window::m_GLFWevents = { -1,-1,-1,-1,-1 };

    glfwMouseEvent Fr_Window::mouseEvent = { 0 };
    GLFWwindow* Fr_Window::pGLFWWindow = nullptr;
    bool Fr_Window::MouseOnce = true;

    const screenDim_t Fr_Window::getScreenDim(void) {
        return m_ViewPort;
    }

    static void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    /** end Fr_Window */
    screenDim_t Fr_Window::m_ViewPort{ 50,50, 800,600 };

    Fr_Window::Fr_Window(int x, int y, int w, int h, std::string label) :
        activeScene(nullptr),
        MainWinCursor(0), panelWidth(0.f),
        gl_version_major(4), gl_version_minor(6),
        mouseDefaults{0},showOpenDialog(false),
        radiusXYZ(0.0f),
        runCode(false), m_label(label)
    {
        showOpenDialog=false;
        /** from Fr_Window */
        mouseDefaults.MouseScrollScale = 1.1f;
        mouseDefaults.MouseXYScale = 0.5f;
        gl_version_major = 4;
        gl_version_minor = 6;
        glfwSetErrorCallback(error_callback);
        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            //FRTK_CORE_ASSERT(success, "Could not initialize GLFW!");
            s_GLFWInitialized = true;
        }
        //Hint to GLFW  - Window is visible, not decorated and gl version is 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_DEPTH_BITS, 32);

        radiusXYZ = 0.0f;
        phi = theta = 0.f;
        runCode = true;
        spWindow = this;
        clear_color = ImVec4(FR_WINGS3D);

        cursorHand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
        cursorCrosshair = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);

        m_ViewPort.x = x;
        m_ViewPort.y = y;
        m_ViewPort.h = h;
        m_ViewPort.w = w;
#if 1 //just for debug purpose
    
        RayMousePos.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        RayMousePos.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
 

#endif

 
    }

    /* from Fr_Window*/

    void Fr_Window::flush() {
        glad_glFlush();
    }
    //FIXME
    Fr_Window::~Fr_Window()
    {
        if (cursorHand)      glfwDestroyCursor(cursorHand);
        if (cursorCrosshair) glfwDestroyCursor(cursorCrosshair);
    }

    Fr_Window* Fr_Window::getFr_Window(void)
    {
        return spWindow;
    }

 

    /**
    * Exit application and destroy both windows.
    */
    int Fr_Window::Exit()
    {
        if (pGLFWWindow)
        {
            glfwSetWindowShouldClose(pGLFWWindow, true);
            glfwPollEvents();
            return 0;
        }
        return 0;
    }

    GLFWwindow* Fr_Window::getCurrentGLWindow()
    {
        return pGLFWWindow;
    }
    /**
     * Main Scene creation. It creates the cameras, Grid, Axis, and Navigation box (Not implemented yet)
     *
     */
    void Fr_Window::CreateScene()
    {
        activeScene = std::make_shared<Fr_Scene>();
    }

    void Fr_Window::resizeWindow(int xGl, int yGl, int wGl, int hGl)
    {
        //Use this to resize the GLFW window regardless the ratio
        m_ViewPort = { xGl,yGl,wGl,hGl };
       }

    //TODO : FIXME : Maybe it is not correct???
    void Fr_Window::hide()
    {
        glfwMakeContextCurrent(nullptr);
        glfwDestroyWindow(pGLFWWindow);
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void Fr_Window::deinitializeGlad()
    {
        s_GladInitialized = false;
    }

    int Fr_Window::x() const
    {
        return m_ViewPort.x;
    }

    int Fr_Window::y() const
    {
        return m_ViewPort.y;
    }

    int Fr_Window::w() const
    {
        return m_ViewPort.w;
    }

    int Fr_Window::h() const
    {
        return m_ViewPort.h;
    }

    const char* Fr_Window::label() const
    {
        return m_label.c_str();
    }

    void Fr_Window::label(std::string l)
    {
        m_label = l;
    }

    void Fr_Window::label(const char* l)
    {
        m_label = l;
    }

    void Fr_Window::setCameraType(uint8_t typOfCamera)
    {
        activeScene->m_active_camera = typOfCamera;
    }

    uint8_t Fr_Window::getCameraType()
    {
        return activeScene->m_active_camera;
    }

    int Fr_Window::createGLFWwindow()
    {
        //***********************************************************************************************
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        pGLFWWindow = glfwCreateWindow(m_ViewPort.w, m_ViewPort.h, m_label.c_str(), NULL, NULL);
        if (pGLFWWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(pGLFWWindow);
        glfwSwapInterval(1);
        glfwSetWindowPos(pGLFWWindow, m_ViewPort.x, m_ViewPort.y);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        s_GladInitialized = true;
        // GLFW callbacks  https://www.glfw.org/docs/3.3/input_guide.html
        glfwSetFramebufferSizeCallback(pGLFWWindow, framebuffer_size_callback);
        glfwSetKeyCallback(pGLFWWindow, keyboard_callback);
        glfwSetCursorPosCallback(pGLFWWindow, cursor_m_positioncallback);
        glfwSetCursorEnterCallback(pGLFWWindow, cursor_enter_callback);
        glfwSetMouseButtonCallback(pGLFWWindow, mouse_button_callback);
        glfwSetScrollCallback(pGLFWWindow, scroll_callback);
        glfwSetJoystickCallback(joystick_callback);
        glfwSetWindowPosCallback(pGLFWWindow, glfwWindPos);
        glfwSetWindowSizeCallback(pGLFWWindow, glfwWindosResize);
        return 1;
    }

    void Fr_Window::joystick_callback(int jid, int events)
    {
    }

    void Fr_Window::resize(int x, int y, int w, int h)
    {
        //This will affect the whole system, glfw and main window
        glfwSetWindowPos(pGLFWWindow, x, y);
        glfwSetWindowSize(pGLFWWindow, w, y);
        //Do we need to send this to the scene and childrens?? TODO: CHECKME!!
    }

    void Fr_Window::show() {
        if (createGLFWwindow() != 0) {
            if (s_GladInitialized == true) {
                //                       TODO: DO WE NEED THIS? I remove it for now
            }
        }
    }

    int Fr_Window::GLFWrun()
    {
       /* FR_PROFILE_FUNCTION();
        FR_PROFILE_SCOPE("GLFWrun");*/

        
       
        panelWidth = 220.0f;
        /**
         *
         * For the layers, We will make :
         *  Main layer which has the dockspace and all other GUI parts and will be default visible object layer
         */
 
        CreateScene();   //Main drawing process.
        activeScene->setupScene();
        ///////////////////////
         // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
         io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        float fontSize = 18.0f;
        std::string path = fontPath + "OpenSans-Bold.ttf";
        io.Fonts->AddFontFromFileTTF(path.c_str(), fontSize);
        path = fontPath + "Open Sans Regular.ttf";
        io.FontDefault = io.Fonts->AddFontFromFileTTF(path.c_str(), fontSize);

        std::string PathICON = fontPath + std::string(FONT_ICON_FILE_NAME_FAS);
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };

        io.Fonts->AddFontFromFileTTF(PathICON.c_str(), ICON_FONT_SIZE, &icons_config, icons_ranges);

        // Setup Dear ImGui style
         //ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
         ImGui::StyleColorsLight();

        GLFWwindow* window = Fr_Window::getCurrentGLWindow();
        assert(window != nullptr);
        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
 
        glfwGetFramebufferSize(pGLFWWindow, &m_ViewPort.w, &m_ViewPort.h);
        userData_ data;



#if 1 //Experimental code TODO: REMOVE ME !! 
        text= std::make_shared<TextRenderer>(m_ViewPort.w,m_ViewPort.h);
        //if (!text->LoadFont("C:/Windows/Fonts/ALGER.ttf", 48)) {
        if (!text->LoadFont(DEFAULT_FONT, 48)) {
            FRTK_CORE_ERROR("FAILED TO LOAD FONT ");
            return 1;
        }
#endif


        while (!glfwWindowShouldClose(pGLFWWindow))
        {
            //ALL 3D Drawings 
            activeScene->RenderScene();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGuizmo::BeginFrame();
            //This Renders all GUI (imGui) widgets and widnows- not viewport. 
            renderimGUI(data);
            ImGuiIO io = ImGui::GetIO();
            if (Fr_Window::getFr_Window() != nullptr) {
                io.DisplaySize = ImVec2(float(Fr_Window::getFr_Window()->w()), float(Fr_Window::getFr_Window()->h()));

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                    GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backupCurrentContext);
                }
            }

            glCheckFunc(glfwSwapBuffers(pGLFWWindow));
            glCheckFunc(glfwPollEvents());
            glViewport(0, 0, w(), h());
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(pGLFWWindow);
        return 0;
    }
    /**
     * Default constructor required by Fr_Window.
     *
     */
     //TODO: Dont know if it is correct
    Fr_Window::Fr_Window()
    {

    }

    int Fr_Window::handle(int events)
    {
        //We need to get the ray always. This will affect performance but don't know how to avoid that
        activeScene->activeRay =  GetScreenToWorldRay();
        return activeScene->handle(events);
    }
    bool Fr_Window::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        return false;
    }
    void Fr_Window::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
 
            SetupLight(modelview, lights);   //Only if the layer is active
    }
    void Fr_Window::Render(RenderInfo& info)
    {

    }
}