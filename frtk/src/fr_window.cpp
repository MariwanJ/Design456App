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

/**
 *
 * This object is a container for the FR_WIDGETS. It has important widget method, property and is their parent :
 * 1- Deliver events
 * 2- Keep track of widgets, add, remove,
 * 3- Layer responsible for the whole FR_WIDGET system (ONLY ONE LAYER AT THE MOMENT, THIS IS A DESIGN QUESTION THAT I DONT KNOW the answer)
 * .
 */
 //NanoVG
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>

#include "fr_window.h"
#include "fr_widget.h"
//#include <glad/glad.h>    // must be included first

#include <gui_widget/frtk_window.h>
#include <gui_widget/demo2.h>
#include <gui_widget/buttons_demo.h>
 /** Fr_Window */

  //Remove me later : TODO
#include<halfedge/fr_shape.h>
/** end fr_grl3 */
namespace FR {
    int Fr_Window::RECURSION_COUNT = 200;
    float Fr_Window::RAY_RANGE = 600;
    GLuint m_QuadVA, m_QuadVB, m_QuadIB;

    bool Fr_Window::s_GLFWInitialized = false;
    bool Fr_Window::s_GladInitialized = false;
    float Fr_Window::m_MousePickerRadius = 5;        //FreeCAD uses 5 pixels as default
    float Fr_Window::phi = 0.0f;
    float Fr_Window::theta = 0.0f;

    std::shared_ptr<Fr_Window> Fr_Window::spWindow = nullptr;

    Fr_InputEvent_t Fr_Window::m_sysEvents{ 0 };

    GLFWwindow* Fr_Window::pGLFWWindow = nullptr;
    bool Fr_Window::MouseOnce = true;

    screenDim_t Fr_Window::getScreenDim(void) {
        return m_ViewPort;
    }
    bool Fr_Window::m_RotateActive = false;
    static void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }
    screenDim_t Fr_Window::m_ViewPort{ {50,50}, {800,600 } };

    SelectionMode  m_currentSelMode = SelectionMode::MESH;

    // Destructor
    Fr_Window::~Fr_Window() {
    }

    // Singleton accessor
    std::shared_ptr<Fr_Window> Fr_Window::getFr_Window(int x, int y, int w, int h, const std::string& label) {
        return spWindow;
    }
    void Fr_Window::initSystemEvents() {
        auto& ev = m_sysEvents;
        ev.mouse.activeX = -1;
        ev.mouse.activeY = -1;
        ev.mouse.prevX = -1;
        ev.mouse.prevY = -1;
        ev.mouse.mouseEntered = -1;
        ev.mouse.worldPos[0] = 0.0f;
        ev.mouse.worldPos[1] = 0.0f;
        ev.mouse.worldPos[2] = 0.0f;
        ev.mouse.button = -1;
        ev.mouse.isDClick = -1;
        ev.mouse.L_Down = false;
        ev.mouse.R_Down = false;
        ev.mouse.M_Down = false;
        ev.mouse.L_Pressed = false;
        ev.mouse.L_Released = false;
        ev.mouse.L_Drag = false;
        ev.mouse.R_Pressed = false;
        ev.mouse.R_Released = false;
        ev.mouse.R_Drag = false;
        ev.mouse.M_Pressed = false;
        ev.mouse.M_Released = false;
        ev.mouse.M_Drag = false;
        ev.mouse.mouseMoved = false;
        ev.mouse.lastMAction = -1;
        ev.mouse.lastMod = -1;
        memset(ev.keyB.keyDown, 0, sizeof(ev.keyB.keyDown));
        memset(ev.keyB.prevKeyDown, 0, sizeof(ev.keyB.prevKeyDown));

        ev.keyB.lastKey = -1;
        ev.keyB.lastKAction = -1;
        ev.keyB.lastMod = -1;
        ev.keyB.scancode = -1;
        ev.keyB.shiftDown = false;
        ev.keyB.ctrlDown = false;
        ev.keyB.altDown = false;
        ev.keyB.superDown = false;
    }

    Fr_Window::Fr_Window(int x, int y, int w, int h, const std::string& label)
        : m_label(label), showOpenDialog(false),
        cursorHand(nullptr), cursorCrosshair(nullptr),
        runCode(false), activeScene(nullptr), m_nvgContext(nullptr),
        gl_version_major(4), gl_version_minor(6),m_NaviCube(true),
        mouseDefaults{ 0 }, radiusXYZ(0.0f), m_winType(FRTK_WIN_TYPE::NORMAL)
    {
        showOpenDialog = false;

        /** from Fr_Window */
        mouseDefaults.MouseScrollScale = 5.0f;
        mouseDefaults.MouseXYScale = 0.5f;
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
        clear_color = ImVec4(FR_WINGS3D);

        cursorHand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
        cursorCrosshair = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);

        m_ViewPort.pos.x = x;
        m_ViewPort.pos.y = y;
        m_ViewPort.size.h = h;
        m_ViewPort.size.w = w;

        // std::string fname = "R";
         // auto n = loadImage();
          //std::shared_ptr<BYTE> IMG = n.getImage("nofile");
        EXE_CURRENT_DIR = GET_CURRENT_DIRECTORY();
        if (EXE_CURRENT_DIR.find("Error:") != std::string::npos) {
            std::cerr << EXE_CURRENT_DIR << std::endl;  // Print the error message
            exit(1);  // Exit with a non-zero status indicating failure
        }
        printf("Current Dir = %s\n", EXE_CURRENT_DIR.c_str());

#if defined(_WIN32) || defined(_WIN64)
        auto it = EXE_CURRENT_DIR.find("\\bin");
#else
        auto it = EXE_CURRENT_DIR.find("/bin");

#endif
        if (it == std::string::npos) {
            printf("Warning, current dir is %s\n", EXE_CURRENT_DIR.c_str());
        }
        else {
            EXE_CURRENT_DIR.erase(it);
        }
        //DEFAULT_FONT = fontPath + "SUSEMono-Thin.ttf";

        while (true) {
            size_t it = EXE_CURRENT_DIR.find("\\"); // Find the backslash
            if (it != std::string::npos) { // Check if found
                EXE_CURRENT_DIR.replace(it, 1, "/"); // Replace with a forward slash
            }
            else {
                break; // Exit the loop if no more backslashes
            }
        }

        fontPath = EXE_CURRENT_DIR + "/resources/fonts/";

        //NanoVg initialization

        //TODO : Check these flags

        initSystemEvents();
    }

    /* from Fr_Window*/

    void Fr_Window::flush() {
        glad_glFlush();
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
        return m_ViewPort.pos.x;
    }

    int Fr_Window::y() const
    {
        return m_ViewPort.pos.y;
    }

    int Fr_Window::w() const
    {
        return m_ViewPort.size.w;
    }

    int Fr_Window::h() const
    {
        return m_ViewPort.size.h;
    }

    const char* Fr_Window::label() const
    {
        return m_label.c_str();
    }

    void Fr_Window::label(std::string& l)
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
        glfwInit();

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        //---------------
        pGLFWWindow = glfwCreateWindow(m_ViewPort.size.w, m_ViewPort.size.h, m_label.c_str(), NULL, NULL);
        if (pGLFWWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(pGLFWWindow);
        glfwSwapInterval(1);

        glfwSetWindowPos(pGLFWWindow, (int)m_ViewPort.pos.x, (int)m_ViewPort.pos.y);

        // glad: load all OpenGL function pointers
        //----------------------------------
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
        glfwSetWindowPos(pGLFWWindow, x, y);
        glfwSetWindowSize(pGLFWWindow, w, y);
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
        m_nvgContext = nvgCreateGL3(NVG_ANTIALIAS);
        if (!m_nvgContext) {
            FRTK_CORE_FATAL("Failed to create context for NanoVG");
            glfwTerminate();
            std::abort(); // stop execution since we can’t continue
        }
        // Wrap in shared_ptr with proper deleting

        /* FR_PROFILE_FUNCTION();
         FR_PROFILE_SCOPE("GLFWrun");*/

        CreateScene();
        activeScene->setupScene();
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        //System fonts :
        SystemFont.txtFontpath = fontPath + "Techfont.ttf";
        SystemFont.symbFontpath = fontPath + "shapes_ttf.ttf";
        SystemFont.fontSize = 14.0;

        //Define default fonts
        ImFont* toolbarFontRaw = io.Fonts->AddFontFromFileTTF(SystemFont.symbFontpath.c_str(), SystemFont.fontSize);
        SystemFont.toolbarFont = std::shared_ptr<ImFont>(toolbarFontRaw, [](ImFont*) { /* No-op, managed by ImGui */ });

        ImFont* textFontRaw = io.Fonts->AddFontFromFileTTF(SystemFont.txtFontpath.c_str(), SystemFont.fontSize);
        SystemFont.textFont = std::shared_ptr<ImFont>(textFontRaw, [](ImFont*) { /* No-op, managed by ImGui */ });

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

        std::string PathICON = fontPath + std::string("shapes_ttf.ttf");
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        static const ImWchar icons_ranges[] = { ICON_MIN, ICON_MAX, 0 };

        io.Fonts->AddFontFromFileTTF(PathICON.c_str(), FRTK_TOOLBAR_BUTTON_FONT_SIZE, &icons_config, icons_ranges);
        ImGui::StyleColorsLight();

        GLFWwindow* window = Fr_Window::getCurrentGLWindow();
        assert(window != nullptr);

        ImGui_ImplGlfw_InitForOpenGL(window, true);

        ImGui_ImplOpenGL3_Init("#version 460");

        glfwGetFramebufferSize(pGLFWWindow, &m_ViewPort.size.w, &m_ViewPort.size.h);

        userData_t data;
        //Temporary Code -- TODO : Remove Me when you are done with the new GUI SYSTEM !!!!!  2026-01-30 Mariwan
        m_frtkWindow.push_back(runFRTKdemo2());
        m_frtkWindow.push_back(runFRTKdemo());
        while (!glfwWindowShouldClose(pGLFWWindow))
        {
            //ALL 3D Drawings
            activeScene->RenderScene();
            
            renderNewGUI(); //temporary code

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();

            ImGui::NewFrame();
            ImGuizmo::BeginFrame();
            //This Renders all GUI (imGui) widgets and windows- not viewport.
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
            updateInputEvents(); //Process events.
        }

        //IMPORTANT!!!!
        /*destroy everything - Without this,
         destructors will not be initiated before OpenGL destroy the context
         which causes a bug in OpenGL*/
        activeScene->m_world.clear();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        if (cursorHand) glfwDestroyCursor(cursorHand);
        if (cursorCrosshair) glfwDestroyCursor(cursorCrosshair);

        for (auto& w : m_frtkWindow)
            w->remove_all();
        m_frtkWindow.clear();

        ImGui::DestroyContext();
        glfwDestroyWindow(pGLFWWindow);
        return 0;
    }

    bool Fr_Window::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        return false;
    }
    void Fr_Window::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
        SetupLight(modelview, lights);
    }
    void Fr_Window::Render(RenderInfo& info)
    {
    }
    NVGcontext* Fr_Window::getnvgContext(void)
    {
        return m_nvgContext;
    }

    int Fr_Window::renderNewGUI() {
        //We might have multiple windows!!!
        for (auto guiWin : m_frtkWindow)
            guiWin->draw();
        return 0;
    }

    //New system for handling events
    void Fr_Window::updateInputEvents(void) {
        double dx = m_sysEvents.mouse.activeX - m_sysEvents.mouse.prevX;
        double dy = m_sysEvents.mouse.activeY - m_sysEvents.mouse.prevY;
        m_sysEvents.mouse.mouseMoved = (dx != 0.0 || dy != 0.0);

        auto& em = m_sysEvents.mouse;

        // LEFT BUTTON
        em.L_Pressed = (em.button == GLFW_MOUSE_BUTTON_LEFT && em.lastMAction == GLFW_PRESS);
        em.L_Released = (em.button == GLFW_MOUSE_BUTTON_LEFT && em.lastMAction == GLFW_RELEASE);
        em.L_Drag = (em.L_Down && em.mouseMoved);  // true if dragging

        // RIGHT BUTTON
        em.R_Pressed = (em.button == GLFW_MOUSE_BUTTON_RIGHT && em.lastMAction == GLFW_PRESS);
        em.R_Released = (em.button == GLFW_MOUSE_BUTTON_RIGHT && em.lastMAction == GLFW_RELEASE);
        em.R_Drag = (em.R_Down && em.mouseMoved); // true if dragging

        // MIDDLE BUTTON
        em.M_Pressed = (em.button == GLFW_MOUSE_BUTTON_MIDDLE && em.lastMAction == GLFW_PRESS);
        em.M_Released = (em.button == GLFW_MOUSE_BUTTON_MIDDLE && em.lastMAction == GLFW_RELEASE);
        em.M_Drag = (em.M_Down && em.mouseMoved); // true if dragging

        //Keyboard
        auto& ek = m_sysEvents.keyB;
        for (int k = 0; k <= GLFW_KEY_LAST; ++k) {
            bool justPressed = (ek.keyDown[k] && !ek.prevKeyDown[k]);
            bool justReleased = (!ek.keyDown[k] && ek.prevKeyDown[k]);

            // You can store these in temp arrays or call handle()
            if (justPressed || justReleased) {
                ek.lastKey = k;
                ek.lastKAction = justPressed ? GLFW_PRESS : GLFW_RELEASE;
                // SHIFT - CTL - ALT
            }
        }
        // Update prevKeyDown for next frame
        std::copy(std::begin(ek.keyDown), std::end(ek.keyDown), std::begin(ek.prevKeyDown));

        if (em.mouseMoved)       handle(FR_MOUSE_MOVE);
        if (em.L_Pressed)        handle(FR_LEFT_PUSH);
        if (em.L_Released)       handle(FR_LEFT_RELEASE);

        // RIGHT BUTTON
        if (em.R_Pressed)        handle(FR_RIGHT_PUSH);
        if (em.R_Released)       handle(FR_RIGHT_RELEASE);

        // MIDDLE BUTTON
        if (em.M_Pressed)        handle(FR_MIDDLE_PUSH);
        if (em.M_Released)       handle(FR_MIDDLE_RELEASE);

        if (em.L_Drag)           handle(FR_LEFT_DRAG_PUSH);
        if (em.R_Drag)           handle(FR_RIGHT_DRAG_PUSH);
        if (em.M_Drag)           handle(FR_MIDDLE_DRAG_PUSH);

        //Keyboard Events
        for (int k = 0; k <= GLFW_KEY_LAST; ++k) {
            bool justPressed = ek.keyDown[k] && !ek.prevKeyDown[k];
            bool justReleased = !ek.keyDown[k] && ek.prevKeyDown[k];
            if (justPressed || justReleased) {
                ek.lastKey = k;
                ek.lastKAction = justPressed ? GLFW_PRESS : GLFW_RELEASE;
                handle(FR_KEYBOARD);
            }
        }
        //scroll happened
        bool scrollHappened = (em.scrollX != 0.0 || em.scrollY != 0.0);
        if (scrollHappened) {
            handle(FR_SCROLL);
        }
        // Enter, deactivate
        if (em.mouseEntered) {
            handle(FR_ENTER);
        }
        else {
            handle(FR_DEACIVATE);
        }

        // END OF FRAME RESET
        em.prevX = em.activeX;
        em.prevY = em.activeY;

        // Clear edge events
        em.L_Pressed = em.L_Released = false;
        em.R_Pressed = em.R_Released = false;
        em.M_Pressed = em.M_Released = false;
        em.mouseEntered = false;
        ek.lastKey = -1;
        em.lastMAction = -1;
        ek.lastKAction = -1;

        em.mouseMoved = false;
        em.scrollX = 0.0;
        em.scrollY = 0.0;
        spWindow->calculateScreenRay();
    }
    int Fr_Window::handle(int events)
    {
        //send the event
        for (auto gui_win : m_frtkWindow) {
            if (gui_win->handle(events) == 1)
                return 1; //We consumed the event
        }
        auto& em = m_sysEvents.mouse;
        auto& ek = m_sysEvents.keyB;

        switch (events) {
        case FR_MIDDLE_DRAG_PUSH:

            if (!em.mouseMoved)
                break; // nothing to do this frame

            if (ek.shiftDown) {
                // Pan the camera
                this->cameraPAN(pGLFWWindow);
                return 1;
            }
            else {
                // Rotate the camera
                this->cameraRotate(pGLFWWindow);
                return 1;
            }
            break;
        case FR_SCROLL: {
            cameraZoom(pGLFWWindow);
            return 1;
        }break;
        default: {}
        }
        return activeScene->handle(events);
    }
    void Fr_Window::deactivateNavi()
    {
        m_NaviCube = false;
    }

    void Fr_Window::activateNavi()
    {
        m_NaviCube = true;
    }
}