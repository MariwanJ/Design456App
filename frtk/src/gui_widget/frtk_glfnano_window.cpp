//NanoVG
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>
#include <fr_core.h>
#include<gui_widget/frtk_glfnano_window.h>

namespace FR {
    Frtk_GlfwNano_Window::Frtk_GlfwNano_Window(int X, int Y, int W, int H, std::string lbl) :
        gl_version_major(4), gl_version_minor(6), m_vg(nullptr), m_linkToMainWindow(nullptr){
        // Initialize GLFW
        if (!glfwInit()) {
            FRTK_CORE_FATAL("Failed to initialize GLFW");
        }

        // Create a GLFW window with OpenGL 3.3 core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWwindow* m_glfwWindow = glfwCreateWindow(800, 600, "NanoVG Minimal", NULL, NULL);
        if (!m_glfwWindow) {
            FRTK_CORE_FATAL("Failed to create GLFW");
            glfwTerminate();
        }
        glfwMakeContextCurrent(m_glfwWindow);
        m_vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        if (!m_vg) {
            FRTK_CORE_FATAL("Could not init NanoVG.");
            glfwTerminate();
        }
    }
    void Frtk_GlfwNano_Window::setlinkToMain(Fr_Window* window) {
        m_linkToMainWindow = window;
    }
    void Frtk_GlfwNano_Window::setDecorated(GLFWwindow* w, bool decorated)
    {
        glfwSetWindowAttrib(w, GLFW_DECORATED, decorated);
    }

    const std::string& Frtk_GlfwNano_Window::label()
    {
        return m_label;
    }

    int Frtk_GlfwNano_Window::run(void) {
        while (!glfwWindowShouldClose(m_glfwWindow)) {
            int winWidth, winHeight;
            glfwGetFramebufferSize(m_glfwWindow, &winWidth, &winHeight);
            glViewport(0, 0, winWidth, winHeight);
            glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            // Start NanoVG frame
            nvgBeginFrame(m_vg, winWidth, winHeight, 1.0f);

            // Draw a line
            nvgBeginPath(m_vg);
            nvgMoveTo(m_vg, 100, 100);   // start point
            nvgLineTo(m_vg, 700, 500);   // end point
            nvgStrokeColor(m_vg, nvgRGB(255, 0, 0)); // red line
            nvgStrokeWidth(m_vg, 2.0f);
            nvgStroke(m_vg);

            nvgEndFrame(m_vg);

            glfwSwapBuffers(m_glfwWindow);
            glfwPollEvents();
        }

        // Cleanup
        nvgDeleteGL3(m_vg);
        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
        return 0;
    }

    int Frtk_GlfwNano_Window::x()
    {
        return m_x;
    }
    int Frtk_GlfwNano_Window::y()
    {
        return m_y;
    }
    int Frtk_GlfwNano_Window::w()
    {
        return m_w;
    }
    int Frtk_GlfwNano_Window::h()
    {
        return m_h;
    }
    void Frtk_GlfwNano_Window::x(int X)
    {
        m_x = X;
    }
    void Frtk_GlfwNano_Window::y(int Y)
    {
        m_y = Y;
    }
    void Frtk_GlfwNano_Window::w(int W)
    {
        m_w = W;
    }
    void Frtk_GlfwNano_Window::h(int H)
    {
        m_h = H;
    }
    void Frtk_GlfwNano_Window::position(int X, int Y)
    {
        m_x = X;
        m_y = Y;
        glfwSetWindowPos(m_glfwWindow, X, Y);
    }
}