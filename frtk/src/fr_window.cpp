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

#include <fr_window.h>
#include <fr_widget.h>



#if 1 //Temporary code  - testing gui toolkit
#include <gui_widget/frtk_window.h>
#include <gui_widget/examples/demo2.h>
#include <gui_widget/examples/buttons_demo.h>
#include <gui_widget/examples/input_output.h>
#include <gui_widget/frtk_toolbarwin.h>
#include <gui_widget/examples/tab_widget_show.h>
#endif 

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

        ev.keyB.lastKey = -1;
        ev.keyB.lastKAction = -1;
        ev.keyB.lastMod = -1;
        ev.keyB.scancode = -1;
        ev.keyB.shiftDown = false;
        ev.keyB.ctrlDown = false;
        ev.keyB.altDown = false;
        ev.keyB.superDown = false;
    }
    Fr_InputEvent_t Fr_Window::m_sysEvents = {
        // mouse
        {
            0.0, 0.0,   // activeX, activeY
            0.0, 0.0,   // prevX, prevY
            0.0, 0.0,   // scrollX, scrollY
            false, false, false,   // L_Down, R_Down, M_Down
            false, false, false,   // L_Pressed, L_Released, L_Drag
            false, false, false,   // R_Pressed, R_Released, R_Drag
            false, false, false,   // M_Pressed, M_Released, M_Drag
            false, false, false,   //L_WasDragging ,R_WasDragging, M_WasDragging;
            false, false, false,   //L_DragReleased ,R_DragReleased, M_DragReleased;
            false,                // mouseMoved
            false,                // mouseEntered
            -1, 0,                // lastMAction, lastMod
            glm::vec3(0.0f),      // worldPos
            -1, 0                 // button, isDClick
        },
        // keyboard
        {
            {},                   // keyDown array will zero-initialize
            {},                   // events vector empty
            -1, -1,               // lastKey, lastKAction
            0, 0,                 // scancode, lastMod
            false, false, false, false // shift, ctrl, alt, super
        }
    };

    Fr_Window::Fr_Window(int x, int y, int w, int h, const std::string& label)
        : m_label(label),
        cursorHand(nullptr),
        cursorCrosshair(nullptr),
        runCode(false),
        activeScene(nullptr),
        m_nvgContext(nullptr),
        gl_version_major(4),
        gl_version_minor(6),
        m_NaviCube(true),
        m_MainToolbar(nullptr),
        mouseDefaults{ 0 },
        radiusXYZ(0.0f),
        m_winType(FRTK_WIN_TYPE::NORMAL),
        m_menuHeight(5.0f)
    {
        /** from Fr_Window */
        mouseDefaults.MouseScrollScale = 5.0f;
        mouseDefaults.MouseXYScale = 0.5f;
        glfwSetErrorCallback(error_callback);
        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            FRTK_CORE_APP_ASSERT(success, "Could not initialize GLFW!");
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

        EXE_CURRENT_DIR = GET_CURRENT_DIRECTORY();
        if (EXE_CURRENT_DIR.find("Error:") != std::string::npos) {
            std::cerr << EXE_CURRENT_DIR << std::endl;  // Print the error message
            exit(1);  // Exit with a non-zero status indicating failure
        }
        std::cout << EXE_CURRENT_DIR << std::endl;

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
            it = EXE_CURRENT_DIR.find("\\");
            if (it != std::string::npos) {
                EXE_CURRENT_DIR.replace(it, 1, "/"); // Replace with a forward slash
            }
            else {
                break;
            }
        }

        fontPath = EXE_CURRENT_DIR + "/resources/fonts/";
        iconPath = EXE_CURRENT_DIR + "/resources/icons/32x32/";
        initSystemEvents();
    }

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
        glfwSetCharCallback(pGLFWWindow, char_callback);
        glfwSetCursorPosCallback(pGLFWWindow, cursor_m_positioncallback);
        glfwSetCursorEnterCallback(pGLFWWindow, cursor_enter_callback);
        glfwSetMouseButtonCallback(pGLFWWindow, mouse_button_callback);
        glfwSetScrollCallback(pGLFWWindow, scroll_callback);
        glfwSetJoystickCallback(joystick_callback);
        glfwSetWindowPosCallback(pGLFWWindow, glfwWindPos);
        glfwSetWindowSizeCallback(pGLFWWindow, glfwWindosResize);
        return 1;
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
            std::abort(); // stop execution since we can't continue
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
        FRTK_CORE_APP_ASSERT(window != nullptr);

        ImGui_ImplGlfw_InitForOpenGL(window, true);

        ImGui_ImplOpenGL3_Init("#version 460");

        glfwGetFramebufferSize(pGLFWWindow, &m_ViewPort.size.w, &m_ViewPort.size.h);

        userData_t data;
        //Temporary Code -- TODO : Remove Me when you are done with the new GUI SYSTEM !!!!!  2026-01-30 Mariwan
       // auto TB = runFRTKdemo2();
       // m_frtkWindow.emplace_back(TB);
        //m_frtkWindow.push_back(runFRTKdemo());
       // m_frtkWindow.push_back(runInputOutput());

        m_frtkWindow.emplace_back(runTabWidget());
        //TOOLBAR CREATION  - USING NEW GUI TOOLKIT

        m_MainToolbar = createMainToolbar();
        m_MainToolbar->parent(this);
        m_frtkWindow.emplace_back(m_MainToolbar);

        m_selectionTB = createSelectionToolbar();
        m_selectionTB->parent(this); //do not forget this !!!
        m_frtkWindow.emplace_back(m_selectionTB);
        bool onlyOnce = false;
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

            io = ImGui::GetIO();

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
            if (!onlyOnce) {
                m_MainToolbar->y(m_menuHeight + 1);
                m_selectionTB->y(m_menuHeight + 1);
                onlyOnce = true;
            }
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
        /*
            Important to remember!!!
            If you have only one GLFW windows, you should
            NEVER call nvgBeginFrame/nvgEndFrame per windows.
            use nvgBeginFrame/nvgEndFrame  per each GLFW windows once!!

        */
        float ratio = activeScene->getActiveCamera().getRatio();
        nvgBeginFrame(m_nvgContext, (float)w(), (float)h(), ratio);
        for (auto guiWin : m_frtkWindow) {
            guiWin->draw();
        }
        nvgEndFrame(m_nvgContext);
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

        //Dragging update :
        // Track if drag ever happened during this button-down session
        if (em.L_Drag) em.L_WasDragging = true;
        if (em.R_Drag) em.R_WasDragging = true;
        if (em.M_Drag) em.M_WasDragging = true;

        // Drag released = button released AND was dragging this session
        em.L_DragReleased = em.L_Released && em.L_WasDragging;
        em.R_DragReleased = em.R_Released && em.R_WasDragging;
        em.M_DragReleased = em.M_Released && em.M_WasDragging;

        // Clear WasDragging when button is released
        if (em.L_Released) em.L_WasDragging = false;
        if (em.R_Released) em.R_WasDragging = false;
        if (em.M_Released) em.M_WasDragging = false;

        //Keyboard
        auto& ek = m_sysEvents.keyB;
        for (auto& e : ek.events) {
            ek.lastKey = e.key;
            ek.lastKAction = e.action;
            ek.lastMod = e.mods;
            handle(FR_KEYBOARD);
        }
        ek.events.clear(); //clear events as we processed them.

        if (em.mouseMoved)       handle(FR_MOUSE_MOVE);
        if (em.L_Pressed)        handle(FR_LEFT_PUSH);
        if (em.L_Released)       handle(FR_LEFT_RELEASE);

        // RIGHT BUTTON
        if (em.R_Pressed)        handle(FR_RIGHT_PUSH);
        if (em.R_Released)       handle(FR_RIGHT_RELEASE);

        // MIDDLE BUTTON
        if (em.M_Pressed)        handle(FR_MIDDLE_PUSH);
        if (em.M_Released)       handle(FR_MIDDLE_RELEASE);

        if (em.L_Drag) {
            if (!em.L_WasDragging) {
                // Started drag this frame
                handle(FR_LEFT_DRAG_PUSH);
            }
            else {
                // Continuing drag
                handle(FR_LEFT_DRAG_MOVE);
            }
        }
        if (em.R_Drag) {
            if (!em.R_WasDragging) {
                handle(FR_RIGHT_DRAG_PUSH);
            }
            else {
                handle(FR_RIGHT_DRAG_MOVE);
            }
        }
        if (em.M_Drag) {
            if (!em.M_WasDragging) {
                handle(FR_MIDDLE_DRAG_PUSH);
            }
            else {
                handle(FR_MIDDLE_DRAG_MOVE);
            }
        }

        if (em.L_DragReleased) handle(FR_LEFT_DRAG_RELEASE);
        if (em.R_DragReleased) handle(FR_RIGHT_DRAG_RELEASE);
        if (em.M_DragReleased) handle(FR_MIDDLE_DRAG_RELEASE);

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
        //FRTK GUI HANDLE
        for (auto it = m_frtkWindow.rbegin(); it != m_frtkWindow.rend(); ++it)
        {
            std::shared_ptr<Frtk_Window> gui_win = *it;

            if (gui_win->handle(events) == 1)
                return 1; // consumed by a child widget

            if (events == FR_LEFT_PUSH)
            {
                if (gui_win->isMouse_inside())
                    gui_win->take_focus();
                else
                    gui_win->lose_focus();
            }
            else
                //Further down Keyboard translation :
                if (events == FR_KEYBOARD) {
                    if (g_focusedWdgt.keyboardOwner) {
                        
                        auto& ek = m_sysEvents.keyB;
                        int action = ek.lastKAction;

                        if (action == GLFW_PRESS) {
                            if (g_focusedWdgt.current &&
                                g_focusedWdgt.keyboardOwner->m_guiWindow->send_event(*g_focusedWdgt.current, FR_KEYBOARD) == 1)
                            {
                                return 1; // consumed by the widget
                            }
                            
                            int key = ek.lastKey;
                            switch (key) {
                            case GLFW_KEY_TAB:
                            case GLFW_KEY_RIGHT:
                            case GLFW_KEY_DOWN:
                            case GLFW_KEY_LEFT:
                            case GLFW_KEY_UP:
                            {
                                // Compute next focusable widget in this GUI window
                                Frtk_Widget* next = nullptr;

                                if (g_focusedWdgt.current) {
                                    // There is a focused child -> find next widget inside the window
                                    Frtk_Widget* w = g_focusedWdgt.current;
                                    while (w->parent() && !dynamic_cast<Frtk_Window*>(w->parent()))
                                    {
                                        w = w->parent();
                                    }

                                    // Use tree traversal starting from topGroup
                                    Frtk_GrpWidget* topGroup = dynamic_cast<Frtk_GrpWidget*>(w);
                                    if (topGroup->navigate_focus(key))
                                        next = topGroup->focusedChild();
                                }
                                else {
                                    // No focused widget -> pick first focusable child
                                    if (g_focusedWdgt.keyboardOwner->m_guiWindow->navigate_focus(key))
                                        next = g_focusedWdgt.keyboardOwner->m_guiWindow->focusedChild();
                                }

                                if (next) {
                                    g_focusedWdgt.prev = g_focusedWdgt.current;
                                    g_focusedWdgt.current = next;
                                    // notify the widget it gained focus
                                    g_focusedWdgt.keyboardOwner->m_guiWindow->send_event(*next, FR_FOCUS);
                                }
                                return 1; // event consumed
                            }

                            default:
                                // Other keys -> forward to focused widget if any
                                if (g_focusedWdgt.current) {
                                    g_focusedWdgt.keyboardOwner->m_guiWindow->send_event(*g_focusedWdgt.current, FR_KEYBOARD);
                                    return 1;
                                }
                                break;
                            }
                        }
                    }
                }
        }
        //at the end, we should forward the events
        if (g_focusedWdgt.keyboardOwner) {
            if (g_focusedWdgt.keyboardOwner->handle(events)) {
                return 1; //consumed.
            }
        }
        //SCENE PART
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
        }
        default: {}
        }
        // Send event to Scene Container (Mesh objects)
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
    float  Fr_Window::menuHeight(void) const {
        return m_menuHeight;
    }
}