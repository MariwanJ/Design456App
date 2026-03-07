//NanoVG
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>
#include <fr_core.h>
#include<gui_widget/frtk_glfnano_window.h>
#include <gui_widget/frtk_draw.h>
#include "frtk_popup_window.h"

namespace FR {
    Frtk_Popup_Window::Frtk_Popup_Window(int X, int Y, int W, int H, std::string lbl, BOX_TYPE b):
        Frtk_GrpWidget(nullptr,X,Y,W,H,lbl,b),
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
        while (!glfwWindowShouldClose(m_glfwWindow)) {
            int winWidth, winHeight;
            glfwGetFramebufferSize(m_glfwWindow, &winWidth, &winHeight);
            glViewport(0, 0, winWidth, winHeight);
            glClearColor(FR_GRAY);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            nvgBeginFrame(m_vg, m_w, m_h    , 1.0f);
            draw();
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
    void Frtk_Popup_Window::position(float X, float Y)
    {
        m_x = (int)X;
        m_y = (int)Y;
        glfwSetWindowPos(m_glfwWindow, X, Y);
}