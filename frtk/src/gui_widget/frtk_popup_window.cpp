//NanoVG
 

#include<gui_widget/frtk_popup_window.h>
#include <gui_widget/frtk_draw.h>

namespace FR {
    static void error_callback(int error, const char* description)
    {
        (void)error;
        fprintf(stderr, "Error: %s\n", description);
    }

    Frtk_Popup_Window::Frtk_Popup_Window(int X, int Y, int W, int H, std::string lbl, BOX_TYPE b) :
        Frtk_GrpWidget(nullptr, X, Y, W, H, lbl, b), m_glfpopWindow(nullptr), s_GladInitialized(false),
        s_GLFWpopInitialized(false),
        gl_version_major(4), gl_version_minor(6), m_linkToMainWindow(nullptr) {
        // Initialize GLFW
        if (!glfwInit()) {
            FRTK_CORE_FATAL("Failed to initialize GLFW");
        }

        // Create a GLFW window with OpenGL 3.3 core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_glfpopWindow = glfwCreateWindow(800, 600, "NanoVG Minimal", NULL, NULL);
        
        glfwSetErrorCallback(error_callback);
        if (!s_GLFWpopInitialized)
        {
            int success = glfwInit();
            FRTK_CORE_APP_ASSERT(success, "Could not initialize GLFW!");
            s_GLFWpopInitialized = true;
        }

        if (!m_glfpopWindow) {
            FRTK_CORE_FATAL("Failed to create GLFW");
            glfwTerminate();
        }
 
        glfwMakeContextCurrent(m_glfpopWindow);
        glfwSwapInterval(1);

        glfwSetWindowPos(m_glfpopWindow,m_x, m_y);

        // glad: load all OpenGL function pointers
        //----------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return ;
        }
        s_GladInitialized = true;
        // GLFW callbacks  https://www.glfw.org/docs/3.3/input_guide.html
        glfwSetFramebufferSizeCallback(m_glfpopWindow, framebuffer_size_callback);
        glfwSetKeyCallback(m_glfpopWindow, keyboard_callback);
        glfwSetCharCallback(m_glfpopWindow, char_callback);
        glfwSetCursorPosCallback(m_glfpopWindow, cursor_m_positioncallback);
        glfwSetCursorEnterCallback(m_glfpopWindow, cursor_enter_callback);
        glfwSetMouseButtonCallback(m_glfpopWindow, mouse_button_callback);
        glfwSetScrollCallback(m_glfpopWindow, scroll_callback);
        glfwSetJoystickCallback(joystick_callback);
        glfwSetWindowPosCallback(m_glfpopWindow, glfwWindPos);
        glfwSetWindowSizeCallback(m_glfpopWindow, glfwWindosResize);

        m_vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        if (!m_vg) {
            FRTK_CORE_FATAL("Could not init NanoVG.");
            glfwTerminate();
        }
    }
    void Frtk_Popup_Window::setlinkToMain(Fr_Window* window) {
        m_linkToMainWindow = window;
    }
    void Frtk_Popup_Window::setDecorated(GLFWwindow* w, bool decorated)
    {
        glfwSetWindowAttrib(w, GLFW_DECORATED, decorated);
    }
    int Frtk_Popup_Window::handle(int ev)
    {
        return 0;
    }

    void Frtk_Popup_Window::draw() {
        if (!m_visible)
            return;
        FRTK_CORE_APP_ASSERT(m_vg != nullptr);
        draw_box(m_vg, m_boxType, { { m_x, m_y }, { m_w, m_y } }, 0.0f, FRTK_NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        Frtk_GrpWidget::draw_children();
        if (!m_label.empty())
            drawLabel();
        draw_focus();
    }
    int Frtk_Popup_Window::run(void) {
        while (!glfwWindowShouldClose(m_glfpopWindow)) {
            int winWidth, winHeight;
            glfwGetFramebufferSize(m_glfpopWindow, &winWidth, &winHeight);
            glViewport(0, 0, winWidth, winHeight);
            glClearColor(FR_GRAY);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            nvgBeginFrame(m_vg, m_w, m_h, 1.0f);
            draw();
            nvgEndFrame(m_vg);
            glfwSwapBuffers(m_glfpopWindow);
            glfwPollEvents();
        }

        // Cleanup
        nvgDeleteGL3(m_vg);
        glfwDestroyWindow(m_glfpopWindow);
        glfwTerminate();
        return 0;
    }
    void Frtk_Popup_Window::position(float X, float Y)
    {
        m_x = (int)X;
        m_y = (int)Y;
        glfwSetWindowPos(m_glfpopWindow, X, Y);
    }
}