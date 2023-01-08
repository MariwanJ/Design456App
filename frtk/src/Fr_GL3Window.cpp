/*                                                                      *
 This file is a part of the Open Source Design456App                    *
                                                                        *
 Copyright (C) 2023                                                     *
                                                                        *
                                                                        *
 This library is free software; you can redistribute it and/or          *
 modify it under the terms of the GNU Lesser General Public             *
 License as published by the Free Software Foundation; either           *
 version 2 of the License, or (at your option) any later version.       *
                                                                        *
 This library is distributed in the hope that it will be useful,        *
 but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 Lesser General Public License for more details.                        *
                                                                        *
 You should have received a copy of the GNU Lesser General Public       *
 License along with this library; if not, If not, see                   *
 <http://www.gnu.org/licenses/>                                         *
 Author :Mariwan Jalal    mariwan.jalal@gmail.com                       *
*/
//#include <GLFW/glfw3.h>
//#include <GLFW/glfw3native.h>
#include<Fr_GL3Window.h>

GLuint m_QuadVA, m_QuadVB, m_QuadIB;
bool s_GLFWInitialized;
#define border 0

void pfltkWindow_close_cb(Fr_GL3Window* w, void* v) {
    Fr_GL3Window* win = (Fr_GL3Window*)v;
    win->exit();
}

GLFWwindow* Fr_GL3Window::pWindow = nullptr;

bool Fr_GL3Window::s_GLFWInitialized = false;
bool Fr_GL3Window::s_GladInitialized = false;

static int counter = 0;

int Fr_GL3Window::_xGl = 0;
int Fr_GL3Window::_yGl = 0;
int Fr_GL3Window::_wGl = 0;
int Fr_GL3Window::_hGl = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void cursor_position_callback(GLFWwindow*, double xpos, double ypos)
{
}

void cursor_enter_callback(GLFWwindow*, int entered)
{
}

void mouse_button_callback(GLFWwindow*, int button, int action, int mods)
{
}

void scroll_callback(GLFWwindow*, double xoffset, double yoffset)
{
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h, const char* l) : Fl_Widget(x, y, w, h, l), overlay(false) {
    /*
    * from https://discourse.glfw.org/t/attach-a-glfwwindow-to-windows-window-client-area/882/5:
    *
    BEFORE you #include your glfw includes, define the native win32 glfw exposure such as:

    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3.h>
    #include <GLFW/glfw3native.h>

    Next, make sure to include the glfw3native.h as shown above. Clean and rebuild and you should then have access to the function �HWND glfwGetWin32Window(GLFWwindow *window)� which returns a HWND handle from your GLFWwindow
    Next, create a static control or dialog to use as the parent.
    Somehwere in your code after both the control/dialog and GLFWwindow have been instanciated get the HWND handle and change its style to be a chiild as follows:

    DWORD style = GetWindowLong(handle, GWL_STYLE); //get the b style
    style &= ~(WS_POPUP | WS_CAPTION); //reset the �caption� and �popup� bits
    style |= WS_CHILD; //set the �child� bit
    SetWindowLong(handle, GWL_STYLE, style); //set the new style of b
    The
    window->SetParent(control);
    window->MoveWindow(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top); //place b at (x,y,w,h) in a
    control->UpdateWindow();
    */

    //TODO FIXME//

    _xGl = border;
    _yGl = border;
    _wGl = w - border;
    _hGl = h - border;
    gl_version_major = 4;
    gl_version_minor = 3;
    glfwSetErrorCallback(error_callback);

    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        //FRTK_CORE_ASSERT(success, "Could not intialize GLFW!");
        //glfwSetErrorCallback(GLFWErrorCallback);
        s_GLFWInitialized = true;
    }
    //Hint to GLFW  - Window is visible, not decorated and gl version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    pfltkWindow = new Fl_Double_Window(x, y, w, h, l);
    pfltkWindow->callback((Fl_Callback*)pfltkWindow_close_cb, (void*)this);
}

void Fr_GL3Window::flush() {
    updateGLFWWindow();
    Fl::flush();
}
Fr_GL3Window::~Fr_GL3Window()
{
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    pWindow = nullptr;
    if (pfltkWindow) {
        pfltkWindow->hide();
    }
}

int Fr_GL3Window::exit()
{
    glfwDestroyWindow(pWindow);
    pfltkWindow->~Fl_Double_Window();
    return 1;
}

void Fr_GL3Window::draw() {
    if (overlay) {
        pfltkWindow->damage(FL_DAMAGE_ALL); // TODO: FIXME: Or redraw?
        updateGLFWWindow();
        //FRTK_CORE_INFO("[DRAW BOTH] {0}");
        printf("overlay%i\n", counter);
        counter++;
    }
    else {
        updateGLFWWindow();
        pfltkWindow->damage(FL_DAMAGE_ALL);
        // printf("not overlay%i\n", counter);
        counter++;
    }
}

void Fr_GL3Window::reset() {
    shaderProgram = 0;
    gl_texture_reset();
}

void Fr_GL3Window::resizeGlWindow(int _xG, int _yG, int _wG, int _hG)
{
    _xG = border;
    _yG = border;
    _wG = w() - border;
    _hG = h() - border;

    if (pWindow != nullptr) {
        glfwSetWindowPos(pWindow, _xG, _yG);
        glfwSetWindowSize(pWindow, _wG, _hG);
        //printf("xgl=%i ygl=%i wgl=%i hgl=%i\n", _xG, _yG, _wG, _hG);
    }
    if (s_GladInitialized)
        updateGLFWWindow();
}

int Fr_GL3Window::handle(int event) {
    damage(FL_DAMAGE_ALL);

    gladEvents(event);
    return pfltkWindow->handle(event);
}

int Fr_GL3Window::glfw_handle(int evenet)
{
    return 0;
}

void Fr_GL3Window::hide()
{
    glfwMakeContextCurrent(nullptr);
    pfltkWindow->hide();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int Fr_GL3Window::embeddGLfwWindow()
{
    HWND glfwHND = glfwGetWin32Window(pWindow);
    HWND hwParentWindow = fl_win32_xid(pfltkWindow);
    int result = 0;
    if (hwParentWindow == 0) {
        printf("Failed to get HWND of the window please debugme!!\n");
        return 0;
    }

    DWORD style = GetWindowLong(glfwHND, GWL_STYLE); //get the b style
    style &= ~(WS_POPUP | WS_CAPTION); //reset the caption and popup bits
    style |= WS_CHILD; //set the child bit
    //style |= WS_OVERLAPPED;
    SetWindowLong(glfwHND, GWL_STYLE, style); //set the new style of b
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, true); //place b at (x,y,w,h) in a
    SetParent(glfwHND, hwParentWindow);
    UpdateWindow(glfwHND);
    ShowWindow(glfwHND, SW_SHOW);
    return 1;//everything is OK.
}

int Fr_GL3Window::createGLFWwindow()
{
    pWindow = glfwCreateWindow(1000, 800, "", NULL, NULL);
    //GWLF Window construction
    int result = 0;
    if (pWindow != nullptr) {
        glfwMakeContextCurrent(pWindow);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (status == 1) {
            s_GladInitialized = true;
        }
        else
            s_GladInitialized = false;

        if (!s_GladInitialized) {
            std::cout << "Sorry check your code, glad is not initialized\n";
            return 0;
        }
        glfwMakeContextCurrent(pWindow);
        glfwSwapInterval(1);  // GLFW Update rate - interval
        //GLFW_EXPOSE_NATIVE_WIN32
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glfwGetFramebufferSize(pWindow, &_wGl, &_hGl);
       // embeddGLfwWindow();

       // glClear(GL_COLOR_BUFFER_BIT);
       // glViewport(_xGl, _yGl, _wGl, _hGl);

        // GLFW callbacks  https://www.glfw.org/docs/3.3/input_guide.html
        glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
        glfwSetKeyCallback(pWindow, keyboard_callback);
        glfwSetCursorPosCallback(pWindow, cursor_position_callback);
        glfwSetCursorEnterCallback(pWindow, cursor_enter_callback);
        glfwSetMouseButtonCallback(pWindow, mouse_button_callback);
        glfwSetScrollCallback(pWindow, scroll_callback);
        //glfwSetJoystickCallback(joystick_callback);
        result = 1;
    }
    return result;
}
#include <fr_widgets/fr_basic_shapes.h>
int Fr_GL3Window::updateGLFWWindow()
{
    if (s_GladInitialized) {
    }
    return 0;
}

void Fr_GL3Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (s_GladInitialized && s_GLFWInitialized) {
        glViewport(0, 0, _wGl, _hGl);
    }
}

void Fr_GL3Window::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Fr_GL3Window::cursor_position_callback(GLFWwindow*, double xpos, double ypos)
{
}

void Fr_GL3Window::cursor_enter_callback(GLFWwindow*, int entered)
{
}

void Fr_GL3Window::mouse_button_callback(GLFWwindow*, int button, int action, int mods)
{
}

void Fr_GL3Window::scroll_callback(GLFWwindow*, double xoffset, double yoffset)
{
}

void Fr_GL3Window::setOverlay()
{
    overlay = true;
}

void Fr_GL3Window::removeOverlya()
{
    overlay = false;
}

void Fr_GL3Window::show() {
    pfltkWindow->show();
    //Create the GLFW Window
    if (createGLFWwindow() != 0) {
        if (s_GladInitialized == true) {
            //glad_glClearColor(1.0, 0.16, 0.18, 1.0);
            updateGLFWWindow();
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
}

void Fr_GL3Window::gladEvents(int events)
{
    // updateGLFWWindow();
}

void Fr_GL3Window::resize(int x, int y, int w, int h)
{
    _xGl = x + border;
    _yGl = y + border;
    _wGl = w - border;
    _hGl = h - border;

    if (s_GladInitialized) {
        printf("x=%i y=%i w=%i h=%i\n", x, y, w, h);
        resizeGlWindow(_xGl, _yGl, _wGl, _hGl);
        glViewport(_xGl, _yGl, _wGl, _hGl);
        flush();
    }
    pfltkWindow->resize(x, y, w, h);
    pfltkWindow->redraw();
    updateGLFWWindow();
}

void Fr_GL3Window::resizable(Fl_Widget* w)
{
    pfltkWindow->resizable(w);
}

void Fr_GL3Window::redraw()
{
    updateGLFWWindow();
    pfltkWindow->redraw();
}

int Fr_GL3Window::GLFWrun()
{
    while ((Fl_X::first != nullptr) && !glfwWindowShouldClose(pWindow)) {
        updateGLFWWindow();

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // glfwSetKeyCallback(window, key_callback);
        glfwMakeContextCurrent(pWindow);
        glfwSwapInterval(1);
        // NOTE: OpenGL error checks have been omitted for brevity

        unsigned int shader = CreateShader(vertexShaderSource, fragmentShaderSource);
        glUseProgram(shader);
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        while (!glfwWindowShouldClose(pWindow))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glad_glClearColor(1.0, 0.16, 0.18, 1.0);

            //int width, height;
            //glfwGetFramebufferSize(pWindow, &width, &height);
            //const float ratio = width / (float)height;
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            //glViewport(0, 0, width, height);

            draw_triangle(vertexBuffer, pWindow);
            glfwSwapBuffers(pWindow);
            glfwPollEvents();
            //glad_glFlush();
        }
    }
    return 0;
}

Fr_GL3Window::Fr_GL3Window(int w, int h, const char* l) : Fl_Widget(0, 0, w, h, l) {}
Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h) : Fl_Widget(x, y, w, h, "GL3Window") {}
Fr_GL3Window::Fr_GL3Window(int w, int h) : Fl_Widget(0, 0, w, h, "GL3Window") {}