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

#include <frtk.h>
#include <fr_constants.h>
#include <gui_widget/frtk_window.h>
#include <fr_core.h>

namespace FR {
    void Frtk_Window::glfwWindosResize(GLFWwindow* window, int width, int height)
    {
        if (sp_popWindow == nullptr)
            return;
        Frtk_Window* pwin = Frtk_Window::getWindow();
        pwin->m_ViewPort.size.w = width;
        pwin->m_ViewPort.size.h = height;

        glfwGetWindowPos(window, &m_ViewPort.pos.x, &m_ViewPort.pos.y); //update even position
    }
    void Frtk_Window::glfwWindPos(GLFWwindow* window, int pos_x, int pos_y)
    {
        if (sp_popWindow == nullptr)
            return;
        (void)window;
        Frtk_Window* pwin = Frtk_Window::getWindow();
        pwin->m_ViewPort.pos.x = pos_x;
        pwin->m_ViewPort.pos.y = pos_y;
    }
    void Frtk_Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        if (sp_popWindow == nullptr)
            return;
        Frtk_Window* pwin = Frtk_Window::getWindow();
        pwin->m_ViewPort.size.w = width;
        pwin->m_ViewPort.size.h = height;
        if (s_GLFWpopInitialized && s_GLFWpopInitialized) {
            glViewport(0, 0, width, width);
        }
    }

    /*

        window: A pointer to the GLFW window that received the event.
        key: The keyboard key that was pressed or released.
        scancode: The system-specific scancode of the key.
        action: The action that was performed on the key. It can be one of the following values:
            GLFW_PRESS: The key was pressed.
            GLFW_RELEASE: The key was released.
            GLFW_REPEAT: The key was held down and is being repeated.
        mods: Bit field describing which modifier keys (Shift, Control, Alt, Super) were held down.

    */
    void Frtk_Window::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (sp_popWindow == nullptr)
            return; //do nothing
        (void)window;

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            sp_popWindow->Exit();

        Frtk_Window* pwin = Frtk_Window::getWindow();
        auto& ek = pwin->m_sysEvents.keyB;
        ek.lastKey = key;
        ek.scancode = scancode;
        ek.lastKAction = action;
        ek.lastMod = mods;
        ek.shiftDown = (mods & GLFW_MOD_SHIFT) != 0;
        ek.ctrlDown = (mods & GLFW_MOD_CONTROL) != 0;
        ek.altDown = (mods & GLFW_MOD_ALT) != 0;
        ek.superDown = (mods & GLFW_MOD_SUPER) != 0;

        //save key events for pooling later
        ek.events.push_back({ key, scancode, action, mods });
    }

    void Frtk_Window::char_callback(GLFWwindow* window, unsigned int codepoint)
    {
        if (!sp_popWindow) return;
        sp_popWindow->m_unicodeChars.push_back({ codepoint });
    }

    void Frtk_Window::joystick_callback(int jid, int events)
    {
    }
    void Frtk_Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (!sp_popWindow) return;
        auto& em = sp_popWindow->m_sysEvents.mouse;

        // Update button state
        if (button == GLFW_MOUSE_BUTTON_LEFT)       em.L_Down = (action != GLFW_RELEASE);
        else if (button == GLFW_MOUSE_BUTTON_RIGHT) em.R_Down = (action != GLFW_RELEASE);
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE) em.M_Down = (action != GLFW_RELEASE);

        em.button = button;
        em.lastMAction = action;
        em.lastMod = mods;

        double now = glfwGetTime(); // current time for double-click detection

        // Handle press events and double-click
        if (action == GLFW_PRESS)
        {
            if (button == GLFW_MOUSE_BUTTON_LEFT)
            {
                if (now - em.L_lastClickTime <= em.doubleClickThreshold)
                    em.mouseEvents.push_back(FR_LEFT_DCLICK);  // new enum for left double-click
                em.L_lastClickTime = now;
                em.mouseEvents.push_back(FR_LEFT_PUSH);
            }
            else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
            {
                if (now - em.M_lastClickTime <= em.doubleClickThreshold)
                    em.mouseEvents.push_back(FR_MIDDLE_DCLICK);
                em.M_lastClickTime = now;
                em.mouseEvents.push_back(FR_MIDDLE_PUSH);
            }
            else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            {
                if (now - em.R_lastClickTime <= em.doubleClickThreshold)
                    em.mouseEvents.push_back(FR_RIGHT_DCLICK);
                em.R_lastClickTime = now;
                em.mouseEvents.push_back(FR_RIGHT_PUSH);
            }
        }

        // Handle drag release vs normal release
        else if (action == GLFW_RELEASE)
        {
            if (button == GLFW_MOUSE_BUTTON_LEFT)
            {
                if (em.L_Dragging)
                {
                    em.L_Dragging = false;
                    em.mouseEvents.push_back(FR_LEFT_DRAG_RELEASE);
                }
                else
                {
                    em.mouseEvents.push_back(FR_LEFT_RELEASE);
                }
            }
            else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
            {
                if (em.M_Dragging)
                {
                    em.M_Dragging = false;
                    em.mouseEvents.push_back(FR_MIDDLE_DRAG_RELEASE);
                }
                else
                {
                    em.mouseEvents.push_back(FR_MIDDLE_RELEASE);
                }
            }
            else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            {
                if (em.R_Dragging)
                {
                    em.R_Dragging = false;
                    em.mouseEvents.push_back(FR_RIGHT_DRAG_RELEASE);
                }
                else
                {
                    em.mouseEvents.push_back(FR_RIGHT_RELEASE);
                }
            }
        }
    }
    void Frtk_Window::cursor_m_positioncallback(GLFWwindow* window, double xpos, double ypos)
    {
        if (!sp_popWindow)
            return;
        (void)window;
        Frtk_Window* pwin = Frtk_Window::getWindow();
        auto& mouse = pwin->m_sysEvents.mouse;
        mouse.activeX = xpos;
        mouse.activeY = ypos;
        mouse.mouseEvents.emplace_back(FR_MOUSE_MOVE);
    }

    void Frtk_Window::cursor_enter_callback(GLFWwindow* window, int entered)
    {
        if (sp_popWindow == nullptr)
            return; //do nothing
        (void)window;
        Frtk_Window* pwin = Frtk_Window::getWindow();
        if (entered) 
            pwin->m_sysEvents.mouse.mouseEvents.emplace_back(FR_ENTER);
        else
            pwin->m_sysEvents.mouse.mouseEvents.emplace_back(FR_LEAVE);
    }

    void Frtk_Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        if (sp_popWindow == nullptr)
            return;
        (void)window;
        Frtk_Window* pwin = Frtk_Window::getWindow();
        auto& m = pwin->m_sysEvents.mouse;
        m.scrollX = xoffset;
        m.scrollY= yoffset;
        m.mouseEvents.emplace_back(FR_SCROLL);
    }
}