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
#ifndef FRTK_POPUP_WINDOW_H
#define FRTK_POPUP_WINDOW_H

#include <frtk.h>
#include <frtk_api.h>

#include <GLFW/glfw3.h>
#include <fr_core.h>
#include <gui_widget/frtk_grpwidget.h>

namespace FR {
    typedef struct {
        Frtk_Widget* current;
        Frtk_Widget* prev;
        Frtk_Widget* g_underMouse;
    }global_focus_tracker_popup_t;
    extern   global_focus_tracker_popup_t g_PopupWindfocusedWdgt;

    class Frtk_Popup_Window : public Frtk_GrpWidget {
    public:
        Frtk_Popup_Window(int X, int Y, int W, int H, std::string lbl, BOX_TYPE b = FRTK_UP_BOX);

        void setlinkToMain(Fr_Window* window);
        virtual int Exit();
        static GLFWwindow* getCurrentGLWindow();
        static screenDim_t getScreenDim(void);
        static void deinitializeGlad();
        virtual void position(float X, float Y) override;
        virtual void setDecorated(GLFWwindow* w, bool decorated);
        int render_popupWindow(void);
        void initSystemEvents();
        
        static Frtk_Popup_Window* getFrtkPopWindow();

        static Frtk_Popup_Window* sp_popWindow;
        ImVec4 clear_color;
        GLFWcursor* MainWinCursor;
        std::vector<CharEvent_t> m_unicodeChars;

        static Fr_InputEvent_t m_sysEvents;
        virtual void show();

    protected:

        static screenDim_t m_ViewPort;
        GLFWcursor* cursorHand = nullptr;
        GLFWcursor* cursorCrosshair = nullptr;

        static void glfwWindosResize(GLFWwindow* window, int width, int height);
        static void glfwWindPos(GLFWwindow* window, int pos_x, int pos_y);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void char_callback(GLFWwindow* window, unsigned int codepoint);
        static void cursor_m_positioncallback(GLFWwindow* win, double xpos, double ypos);
        static void cursor_enter_callback(GLFWwindow* win, int entered);
        static void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);
        static void joystick_callback(int jid, int events);

        virtual int handle(int ev) override;
        virtual void draw() override;

        static GLFWwindow* m_glfpopWindow;
        int gl_version_major;
        int gl_version_minor;
        Fr_Window* m_linkToMainWindow;
        static bool s_GLFWpopInitialized;
        static bool s_GladpopInitialized;
        void flush();
    };
}
#endif //FRTK_POPUP_WINDOW_H