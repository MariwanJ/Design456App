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

//NanoVG

#include<gui_widget/frtk_popup_window.h>
#include <gui_widget/frtk_draw.h>
#include <frtk.h>
namespace FR {
    static void error_callback(int error, const char* description)
    {
        (void)error;
        fprintf(stderr, "Error: %s\n", description);
    }
    bool Frtk_Popup_Window::s_GLFWpopInitialized = false;
    bool Frtk_Popup_Window::s_GladpopInitialized = false;
    global_focus_tracker_popup_t g_PopupWindfocusedWdgt;
    screenDim_t Frtk_Popup_Window::m_ViewPort = { 0 };
    Frtk_Popup_Window* Frtk_Popup_Window::sp_popWindow = nullptr;
    Fr_InputEvent_t Frtk_Popup_Window::m_sysEvents = {
        // Mouse
         {
            0.0, 0.0,   // activeX, activeY
            0.0, 0.0,   // prevX, prevY
            0.0, 0.0,   // scrollX, scrollY

            false, false, false,   // L_Down, R_Down, M_Down
            false, false, false,   // L_Dragging, R_Dragging, M_Dragging

            false,                // insideglfwWindow
            -1,                   // lastMAction
            0,                    // lastMod
            glm::vec3(0.0f),      // worldPos

            -1,                   // button
            0,                    // isDClick
            0.0, 0.0, 0.0,        // L_lastClickTime, R_lastClickTime, M_lastClickTime
            0.25,                 // doubleClickThreshold
            {}                    // mouseEvents vector
        },
        // Keyboard
         {
            {},                    // keyDown array (will zero-initialize all)
            {},                    // events vector
            -1,                    // lastKey
            -1,                    // lastKAction
            -1,                    // scancode
            0,                     // lastMod
            false, false, false, false // shiftDown, ctrlDown, altDown, superDown
        }
    };

    GLFWwindow* Frtk_Popup_Window::m_glfpopWindow = nullptr;

    Frtk_Popup_Window::Frtk_Popup_Window(int X, int Y, int W, int H, std::string lbl, BOX_TYPE b) :
        Frtk_GrpWidget(nullptr, 0, 0, W, H, lbl, b),
        MainWinCursor(nullptr), glfDim({ {(int)X,(int)Y }, { (int)W,(int)H } }),
        gl_version_major(4), gl_version_minor(6), m_linkToMainWindow(nullptr) {
        // Initialize GLFW
        sp_popWindow = this;
    }
    Frtk_Popup_Window* Frtk_Popup_Window::getFrtkPopWindow() {
        return sp_popWindow;
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
        draw_box(m_vg, m_boxType, { { 0.0f, 0.0f }, { m_w, m_h } }, 0.0f, FRTK_NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        Frtk_GrpWidget::draw_children();
        if (!m_label.empty())
            drawLabel();
        draw_focus();
    }

    void Frtk_Popup_Window::show()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_glfpopWindow = glfwCreateWindow(
            glfDim.size.w, glfDim.size.h,
            "NanoVG Popup",
            NULL,
            m_linkToMainWindow->getCurrentGLWindow() // share context
        );

        if (!m_glfpopWindow)
        {
            FRTK_CORE_FATAL("Failed to create GLFW window");
            return;
        }

        glfwMakeContextCurrent(m_glfpopWindow);
        glfwSwapInterval(1);

        glfwSetWindowPos(m_glfpopWindow, glfDim.pos.x, glfDim.pos.y);

        glfwSetFramebufferSizeCallback(m_glfpopWindow, framebuffer_size_callback);
        glfwSetKeyCallback(m_glfpopWindow, keyboard_callback);
        glfwSetCharCallback(m_glfpopWindow, char_callback);
        glfwSetCursorPosCallback(m_glfpopWindow, cursor_m_positioncallback);
        glfwSetCursorEnterCallback(m_glfpopWindow, cursor_enter_callback);
        glfwSetMouseButtonCallback(m_glfpopWindow, mouse_button_callback);
        glfwSetScrollCallback(m_glfpopWindow, scroll_callback);

        m_vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

        if (!m_vg)
            FRTK_CORE_FATAL("Could not init NanoVG.");
    }
    int Frtk_Popup_Window::render_popupWindow(void) {
        if (m_glfpopWindow) {
            if (!glfwWindowShouldClose(m_glfpopWindow)) {
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
            else {
                glfwMakeContextCurrent(m_glfpopWindow);
                glfwDestroyWindow(m_glfpopWindow);
                glfwMakeContextCurrent(m_linkToMainWindow->getCurrentGLWindow());
                glfwFocusWindow(m_linkToMainWindow->getCurrentGLWindow());
                m_glfpopWindow = nullptr;
            }
        }
        return 0;
    }
    void Frtk_Popup_Window::position(float X, float Y)
    {
        glfDim.pos.x = (int)X;
        glfDim.pos.y = (int)Y;
        glfwSetWindowPos(m_glfpopWindow, X, Y);
    }
    int Frtk_Popup_Window::Exit()
    {
        if (m_glfpopWindow)
        {
            m_children.clear();
            glfwDestroyWindow(m_glfpopWindow);
            m_glfpopWindow = nullptr;
            return 1;
        }
        return 0;
    }
}