//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2023
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

#include<Fr_GL3Window.h>

//Remove me later : TODO
#include<Mesh.h>
#include<ObjectShaderNode.h>
//End remove me later
Scene* Fr_GL3Window::scene = nullptr;
// Fr_GL3Window_fixed.cpp
// Corrected & cleaned version of the original Fr_GL3Window.cpp
// - Fixes glfw init/terminate usage
// - Sets GLFW user pointer to Fr_GL3Window* for safe callbacks
// - Creates GLFW window hidden, embeds it, then shows it
// - Uses Fl::check() inside combined run loop so FLTK receives events
// - Removes manual destructor calls and avoids abortive exit(0) in callbacks
// NOTE: This file assumes the original project header Fr_GL3Window.h and
// the rest of your project classes (Scene, Camera, etc.) exist unchanged.

#include "Fr_GL3Window.h"

// platform / system includes
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winuser.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#else
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <memory>

// Remove-me-later placeholders remain (Mesh, ObjectShaderNode, etc)
#include <Mesh.h>
#include <ObjectShaderNode.h>

// ---------------------------
// Static & globals (kept similar to original structure)
// ---------------------------
GLuint m_QuadVA, m_QuadVB, m_QuadIB;
bool s_GLFWInitialized;
#define redrawFPS float(1.0/10.0)

float Fr_GL3Window::fltktimerValue = 0.0;

double Fr_GL3Window::newTime = 0.0;
double Fr_GL3Window::oldTime = 0.0;

// Keep pointer to the GLFW window and FLTK window as before
GLFWwindow* Fr_GL3Window::pWindow = nullptr;
bool Fr_GL3Window::s_GLFWInitialized = false;
bool Fr_GL3Window::s_GladInitialized = false;
Fr_GL3Window* Fr_GL3Window::GLFWCallbackWrapper::s_fr_glfwwindow = nullptr;

// If your code relied on a global pfltkWindow, we keep a static pointer here
static Fl_Window* pfltkWindow = nullptr;

static int counter = 0;
Fr_GL3Window* FR::globalP_pWindow = nullptr;
int Fr_GL3Window::_xGl = 0;
int Fr_GL3Window::_yGl = 0;
int Fr_GL3Window::_wGl = 0;
int Fr_GL3Window::_hGl = 0;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

// ---------------------------
// Callback used by FLTK when the window close button is pressed
// We do not call exit(0) here; instead we request the GLFW window to close
// and let the main loop clean up gracefully.
// ---------------------------
void pfltkWindow_close_cb(Fr_GL3Window* w, void* v) {
    Fr_GL3Window* win = (Fr_GL3Window*)v;
    if (!win) return;
    win->deinitializeGlad();
    // Request GLFW window to close; the main loop will exit cleanly.
    if (Fr_GL3Window::pWindow) {
        glfwSetWindowShouldClose(Fr_GL3Window::pWindow, GLFW_TRUE);
    }
    // Hide FLTK window so GUI disappears immediately
    win->hide();
}

// ---------------------------
// Constructor
// - Initialize GLFW once per-process
// - Do NOT call glfwInit twice
// ---------------------------
Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h, const char* l)
    : Fl_Window(x, y, w, h, l), Ox(x), Oy(y), Ow(w), Oh(h),
    overlay(false), active_camera_(CameraList::PERSPECTIVE)
{
    FR::globalP_pWindow = this;

    _xGl = x;
    _yGl = y;
    _wGl = w;
    _hGl = h;

    gl_version_major = 4;
    gl_version_minor = 3;
    glfwSetErrorCallback(error_callback);

    // Initialize GLFW exactly once per process
    if (!s_GLFWInitialized) {
        if (!glfwInit()) {
            throw std::runtime_error("Could not initialize GLFW");
        }
        s_GLFWInitialized = true;
        Fr_GL3Window::s_GLFWInitialized = true;
    }

    // Store FLTK pointer for global uses
    pfltkWindow = this;
    // set FLTK close callback (no immediate exit)
    pfltkWindow->callback((Fl_Callback*)pfltkWindow_close_cb, (void*)this);

    // provide sensible defaults for glfw window hints (actual hints set in createGLFWwindow)
}

Fr_GL3Window::~Fr_GL3Window()
{
    // Ensure we've cleaned up GL/GLFW resources; prefer explicit exit() call elsewhere
}

// ---------------------------
// Clean, safe exit. Do not call destructor manually.
// ---------------------------
int Fr_GL3Window::exit()
{
    if (pWindow) {
        glfwDestroyWindow(pWindow);
        pWindow = nullptr;
    }

    // Do not call pfltkWindow->~Fl_Window(); just hide and delete if needed.
    if (pfltkWindow) {
        // If pfltkWindow is not the same instance as this object, delete it
        if (pfltkWindow != this) {
            delete pfltkWindow;
        }
        pfltkWindow = nullptr;
    }

    // Terminate GLFW once when we exit the application.
    if (Fr_GL3Window::s_GLFWInitialized) {
        glfwTerminate();
        Fr_GL3Window::s_GLFWInitialized = false;
    }

    return 1;
}

GLFWwindow* Fr_GL3Window::getCurrentGLWindow()
{
    return pWindow;
}

static Transform* sun = nullptr;

void Fr_GL3Window::CreateScene()
{
    scene = new Scene();
    scene->linkToglfw = pWindow;

    CreateCameras();
    scene->AddNode(CreateSun());
    scene->AddNode(Grid().CreateGrid());
    vert axis = Axis3D().CreateAxis3D();
    scene->AddNode(axis.Red);
    scene->AddNode(axis.Green);
    scene->AddNode(axis.Blue);
}

void Fr_GL3Window::draw()
{
    // Draw FLTK widgets first
    Fl_Window::draw();

    // Optional overlay logic
    if (overlay) {
        // overlay-specific drawing
        // printf("overlay %d\n", counter);
        counter++;
    }
}

void Fr_GL3Window::resizeGlWindow(float ratio)
{
    _wGl = int(float(_wGl) * ratio);
    _hGl = int(float(_hGl) * ratio);
    damage(FL_DAMAGE_ALL);
    updateGLFWWindow();
}

void Fr_GL3Window::resizeGlWindow(int xGl, int yGl, int wGl, int hGl)
{
    _xGl = x() + xGl;
    _yGl = y() + yGl;
    _wGl = wGl;
    _hGl = hGl;
    updateGLFWWindow();
}

int Fr_GL3Window::handle(int event)
{
    return Fl_Window::handle(event);
}

void Fr_GL3Window::hide()
{
    // If we have a GLFW window, unbind context and hide it
    if (pWindow) {
        glfwMakeContextCurrent(nullptr);
        // do not destroy here; let exit() handle destruction
    }
    Fl_Window::hide();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// ---------------------------
// Embed GLFW window into the FLTK window (Win32-specific code)
// Make sure pWindow is valid before calling glfwGetWin32Window
// ---------------------------
int Fr_GL3Window::embeddGLfwWindow()
{
#ifdef _WIN32
    if (!pWindow) return 0;
    HWND glfwHND = glfwGetWin32Window(pWindow);
    HWND hwParentWindow = fl_win32_xid(pfltkWindow);
    if (hwParentWindow == 0 || glfwHND == NULL) {
        printf("Failed to get HWND of one of the windows.\n");
        return 0;
    }

    DWORD style = GetWindowLong(glfwHND, GWL_STYLE);
    style &= ~(WS_POPUP | WS_CAPTION);
    style |= WS_CHILD | WS_OVERLAPPED;
    SetWindowLong(glfwHND, GWL_STYLE, style);
    SetParent(glfwHND, hwParentWindow);
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, TRUE);
    UpdateWindow(glfwHND);
    ShowWindow(glfwHND, SW_SHOW);
    return 1;
#else
    // Non-Windows embedding is platform-specific and not implemented here.
    (void)pWindow; (void)pfltkWindow; (void)_xGl; (void)_yGl; (void)_wGl; (void)_hGl;
    return 0;
#endif
}

int Fr_GL3Window::releaseGLfwWindow()
{
#ifdef _WIN32
    if (!pWindow) return 0;
    HWND glfwHND = glfwGetWin32Window(pWindow);
    HWND hwParentWindow = fl_win32_xid(pfltkWindow);
    if (hwParentWindow == 0 || glfwHND == NULL) {
        printf("Failed to get HWND of one of the windows.\n");
        return 0;
    }

    DWORD style = GetWindowLong(glfwHND, GWL_STYLE);
    style |= (WS_POPUP | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX | WS_SYSMENU | WS_CAPTION);
    SetWindowLong(glfwHND, GWL_STYLE, style);
    SetParent(glfwHND, nullptr);
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, TRUE);
    UpdateWindow(glfwHND);
    ShowWindow(glfwHND, SW_SHOW);
    return 1;
#else
    (void)pWindow; (void)pfltkWindow; (void)_xGl; (void)_yGl; (void)_wGl; (void)_hGl;
    return 0;
#endif
}

void Fr_GL3Window::deinitializeGlad()
{
    s_GladInitialized = false;
}

void Fr_GL3Window::CreateCameras()
{
    for (int i = 0; i < 6; i++) {
        std::shared_ptr camera_ = std::make_shared<Camera>();
        auto camera_trans = std::make_shared<Transform>();
        if (i == 0) {
            camera_trans->AddNode(camera_);
            camera_->SetActive(true);
            camera_trans->Translate(0.6, 0.5, 1.7);
            camera_trans->Rotate(glm::vec3(1, 0, 0), 180);
        }
        else {
            camera_->SetActive(false);
        }
        camera_trans->AddNode(camera_);
        scene->AddNode(camera_trans);
        camera_->setCameraType((CameraList)i);
        auto manipulator = new Manipulator();
        camera_->SetManipulator(std::unique_ptr<Manipulator>(manipulator));
        cameras.push_back(camera_trans);
    }
}

int Fr_GL3Window::createGLFWwindow()
{
    // Do NOT call glfwInit() here; constructor ensured initialization once.

    // create the GLFW window hidden so we can reparent it before showing
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    pWindow = glfwCreateWindow(_wGl, _hGl, "LearnOpenGL", NULL, NULL);
    if (!pWindow) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    // store pointer to our Fr_GL3Window instance so wrappers can forward calls
    glfwSetWindowUserPointer(pWindow, this);
    GLFWCallbackWrapper::setGLFWwindow(this);

    glfwMakeContextCurrent(pWindow);
    glfwSetFramebufferSizeCallback(pWindow, GLFWCallbackWrapper::framebuffer_size_callback);

    // glad: load all OpenGL function pointers (only after the context is current)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    s_GladInitialized = true;
    FR::s_GladInitialized = true;

    // Now embed the native window in FLTK and show it
    embeddGLfwWindow();

    // set standard GLFW callbacks that forward to methods on our instance
    glfwSetKeyCallback(pWindow, GLFWCallbackWrapper::keyboard_callback);
    glfwSetCursorPosCallback(pWindow, GLFWCallbackWrapper::cursor_position_callback);
    glfwSetCursorEnterCallback(pWindow, GLFWCallbackWrapper::cursor_enter_callback);
    glfwSetMouseButtonCallback(pWindow, GLFWCallbackWrapper::mouse_button_callback);
    glfwSetScrollCallback(pWindow, GLFWCallbackWrapper::scroll_callback);
    glfwSetJoystickCallback(GLFWCallbackWrapper::joystick_callback);

    // Show both native and GLFW window now that embedding & GL are ready
    glfwShowWindow(pWindow);

    return 1;
}

int Fr_GL3Window::updateGLFWWindow()
{
#ifdef _WIN32
    if (!pWindow) return -1;
    HWND glfwHND = glfwGetWin32Window(pWindow);
    if (!glfwHND) return -1;
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, TRUE);
    UpdateWindow(glfwHND);
    RedrawWindow(glfwHND, NULL, NULL, RDW_FRAME | RDW_INTERNALPAINT);
    if (s_GladInitialized) {
        glad_glFlush();
    }
#endif
    return 0;
}

void Fr_GL3Window::setOverlay()
{
    overlay = true;
}

void Fr_GL3Window::removeOverlya()
{
    overlay = false;
}

void Fr_GL3Window::show()
{
    Fl_Window::show();
    if (!pWindow) {
        if (createGLFWwindow() < 0) {
            std::cerr << "createGLFWwindow failed" << std::endl;
        }
    }
}

void Fr_GL3Window::resize(int x, int y, int w, int h)
{
    Fl_Window::resize(x, y, w, h);
    float _ratio = float(w * h) / float(Ow * Oh);
    if (s_GladInitialized) {
        if (_ratio != 0.0f)
            resizeGlWindow(_ratio);
    }
    damage(FL_DAMAGE_ALL);
    Fl_Window::draw();
}

void Fr_GL3Window::resizable(Fl_Widget* w)
{
    Fl_Window::resizable(w);
}

// Combined run loop: process both FLTK and GLFW events
int Fr_GL3Window::GLFWrun()
{
    CreateScene();
    glfwSwapInterval(1);
    if (pWindow)
        glfwMakeContextCurrent(pWindow);
    glViewport(0, 0, _wGl, _hGl);

    while (pWindow && !glfwWindowShouldClose(pWindow)) {
        // Let GLFW poll events
        glfwPollEvents();

        // Let FLTK process pending events without blocking
        Fl::check();

        // Update timers and optionally trigger FLTK redraws as before
        newTime = glfwGetTime();
        if (oldTime == 0.0) oldTime = newTime;
        double delta = newTime - oldTime;
        oldTime = newTime;
        fltktimerValue += delta;
        if (fltktimerValue >= redrawFPS) {
            fltktimerValue = 0.0;
            // trigger FLTK redraw
            Fl::redraw();
        }

        // Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // default background color (your macro FR_WINGS3D should be in a header)
        // glClearColor(FR_WINGS3D);

        if (scene) scene->RenderScene();

        if (s_GladInitialized) {
            glfwSwapBuffers(pWindow);
        }
    }

    // Once loop ends, perform cleanup
    exit();
    return 0;
}

std::shared_ptr<Transform> Fr_GL3Window::CreateSun()
{
    sun = new Transform();
    auto sun_height = std::make_shared<Transform>();
    sun_height->Translate(30, 30, 30);
    sun->AddNode(sun_height);

    auto light = std::make_shared<Light>();
    light->SetPosition(0, 0, 0);
    light->SetDiffuse(0.5, 0.5, 0.5);
    light->SetAmbient(1.0f, 1.0f, 1.0f);
    light->EnableShadowMap(glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), glm::ortho<float>(-50, 50, -50, 50, 400, 600));
    sun_height->AddNode(light);
    sun->SetActive(true);
    return std::shared_ptr<Transform>(sun);
}

void Fr_GL3Window::setOpenGLWinowSize(int xGL, int yGL, int wGL, int hGL)
{
    _xGl = xGL;
    _yGl = yGL;
    _wGl = wGL;
    _hGl = hGL;
    resizeGlWindow(_xGl, _yGl, _wGl, _hGl);
}

// GLFWCallbackWrapper forwarding implementation (unchanged logic but safe because setGLFWwindow called)
void Fr_GL3Window::GLFWCallbackWrapper::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (s_fr_glfwwindow) s_fr_glfwwindow->framebuffer_size_callback(window, width, height);
}

void Fr_GL3Window::GLFWCallbackWrapper::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (s_fr_glfwwindow) s_fr_glfwwindow->keyboard_callback(window, key, scancode, action, mods);
}

void Fr_GL3Window::GLFWCallbackWrapper::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (s_fr_glfwwindow) s_fr_glfwwindow->cursor_position_callback(window, xpos, ypos);
}

void Fr_GL3Window::GLFWCallbackWrapper::cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (s_fr_glfwwindow) s_fr_glfwwindow->cursor_enter_callback(window, entered);
}

void Fr_GL3Window::GLFWCallbackWrapper::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (s_fr_glfwwindow) s_fr_glfwwindow->mouse_button_callback(window, button, action, mods);
}

void Fr_GL3Window::GLFWCallbackWrapper::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (s_fr_glfwwindow) s_fr_glfwwindow->scroll_callback(window, xoffset, yoffset);
}

void Fr_GL3Window::GLFWCallbackWrapper::joystick_callback(int jid, int events)
{
    if (s_fr_glfwwindow) s_fr_glfwwindow->joystick_callback(jid, events);
}

void Fr_GL3Window::GLFWCallbackWrapper::setGLFWwindow(Fr_GL3Window* glfwWindow)
{
    GLFWCallbackWrapper::s_fr_glfwwindow = glfwWindow;
}
