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

#include<gui_widget/frtk_rclick_menu_win.h>
#include <gui_widget/frtk_draw.h>
#include <frtk.h>
namespace FR {


    // Callback function for window focus - if it lose focus, destroy the window
    void window_focus_callback(GLFWwindow* window, int focused) {
        if (focused == GLFW_FALSE) {
            // Hide & destroy the window if it loses focus
            glfwMakeContextCurrent(window);
            glfwHideWindow(window);
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }



    Frtk_Rclick_menuWin::Frtk_Rclick_menuWin(int X, int Y, int W, int H, std::string lbl, BOX_TYPE b) :
        Frtk_Window( X, Y, W, H, lbl, b) {
        m_wdgType = FRTK_GLFW_RIGT_CLICK_WIN;

    }
    void Frtk_Rclick_menuWin::show()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_DECORATED, GL_FALSE); //disable decoration 
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  //disable realizable 

        m_glfWindow = glfwCreateWindow(
            glfDim.size.w, glfDim.size.h,
            "NanoVG Popup",
            NULL,
            m_linkToMainWindow->getCurrentGLWindow() // share context
        );

        if (!m_glfWindow)
        {
            FRTK_CORE_FATAL("Failed to create GLFW window");
            return;
        }

        glfwMakeContextCurrent(m_glfWindow);
        glfwSwapInterval(1);

        glfwSetWindowPos(m_glfWindow, glfDim.pos.x, glfDim.pos.y);

        glfwSetFramebufferSizeCallback(m_glfWindow, framebuffer_size_callback);
        glfwSetKeyCallback(m_glfWindow, keyboard_callback);
        glfwSetCharCallback(m_glfWindow, char_callback);
        glfwSetCursorPosCallback(m_glfWindow, cursor_m_positioncallback);
        glfwSetCursorEnterCallback(m_glfWindow, cursor_enter_callback);
        glfwSetMouseButtonCallback(m_glfWindow, mouse_button_callback);
        glfwSetScrollCallback(m_glfWindow, scroll_callback);

        m_vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        
        glfwSetWindowFocusCallback(m_glfWindow, window_focus_callback);

        if (!m_vg)
            FRTK_CORE_FATAL("Could not init NanoVG.");
    }

    }
  
