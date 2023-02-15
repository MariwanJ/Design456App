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

GLuint m_QuadVA, m_QuadVB, m_QuadIB;
bool s_GLFWInitialized;
#define redrawFPS  1.0/25.0  // (24 Frames per sec)

float Fr_GL3Window::fltktimerValue = 0.0;

/*********************************************/

double Fr_GL3Window::newTime = 0.0;
double Fr_GL3Window::oldTime = 0.0;

/***********************/
void pfltkWindow_close_cb(Fr_GL3Window* w, void* v) {
    Fr_GL3Window* win = (Fr_GL3Window*)v;
    win->deinitializeGlad();
    win->exit();
    exit(0);
}

GLFWwindow* Fr_GL3Window::pWindow = nullptr;

bool Fr_GL3Window::s_GLFWInitialized = false;
bool Fr_GL3Window::s_GladInitialized = false;
Fr_GL3Window* Fr_GL3Window::GLFWCallbackWrapper::s_fr_glfwwindow = nullptr;

static int counter = 0;

Fr_GL3Window* FR::globalP_pWindow = nullptr;
int Fr_GL3Window::_xGl = 0;
int Fr_GL3Window::_yGl = 0;
int Fr_GL3Window::_wGl = 0;
int Fr_GL3Window::_hGl = 0;

static void redrawFLTKTimer_cb(void* window) {
    Fr_GL3Window* win = (Fr_GL3Window*)window;
    win->damage(FL_DAMAGE_ALL);
    win->draw();
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

/**
* Class constructor -
* FIXME: CLEANUP CODE
*/
Scene* Fr_GL3Window::scene = nullptr;
Fr_GL3Window::Fr_GL3Window(int x = 0, int y = 0, int w = 900, int h = 800, const char* l = "FLTK_GLFW Test") :Fl_Window(x, y, w, h, l), Ox(x), Oy(y), Ow(w), Oh(h),
overlay(false),
active_camera_(CameraList::PERSPECTIVE) {
    //Default size is the size of the FLTK window
    FR::globalP_pWindow = this;

    _xGl = x;
    _yGl = y;
    _wGl = w;
    _hGl = h;

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
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pfltkWindow = this;
    pfltkWindow->callback((Fl_Callback*)pfltkWindow_close_cb, (void*)this);
}

/**
* Force updating both windows
* TODO:FIXME
*/
void Fr_GL3Window::flush() {
    glad_glFlush();
    Fl::flush();
}

//FIXME
Fr_GL3Window::~Fr_GL3Window()
{
    //exit();
}

/**
* Exit application and destroy both windows.
*/
int Fr_GL3Window::exit()
{
    if (pWindow)
        glfwDestroyWindow(pWindow);
    if (pfltkWindow)
        pfltkWindow->~Fl_Window();
    return 1;
}

GLFWwindow* Fr_GL3Window::getCurrentGLWindow()
{
    return pWindow;
}

static Transform* sun = nullptr;

void Fr_GL3Window::CreateScene()
{
    scene = new Scene();//Save a link to the windows also.
    scene->linkToglfw = pWindow;

    CreateCameras();
    /*
      * Add here the nodes - Grid, and XYZ axis
      */
    scene->AddNode(CreateSun());
    scene->AddNode(bunny());
    scene->AddNode(Grid().CreateGrid());
    vert axis = Axis3D().CreateAxis3D();
    scene->AddNode(axis.Red);
    scene->AddNode(axis.Green);
    scene->AddNode(axis.Blue);
}

//TODO FIXME
void Fr_GL3Window::draw() {
    if (overlay) {
        Fl_Window::draw();
        printf("overlay%i\n", counter);
        counter++;
    }
    else {
        Fl_Window::draw();
        counter++;
    }
    Fl::flush();
}

/**
*Resize only the GLFW Window.
*/
void Fr_GL3Window::resizeGlWindow(float ratio)
{
    //We don't chage _xGl or _hGl
    _wGl = int(float(_wGl) * ratio);
    _hGl = int(float(_hGl) * ratio);
    updateGLFWWindow();
}

void Fr_GL3Window::resizeGlWindow(int xGl, int yGl, int wGl, int hGl)
{
    //Use this to resize the GLFW window regardless the ratio
    _xGl = x() + xGl;
    _yGl = y() + yGl;
    _wGl = wGl;
    _hGl = hGl;
    updateGLFWWindow();
}

int Fr_GL3Window::handle(int event) {
    //gladEvents(event);
    //gladEvents(event);
    return Fl_Window::handle(event);
}

//TODO : FIXME : Maybe it is not correct???
void Fr_GL3Window::hide()
{
    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(pWindow);
    Fl_Window::hide();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int Fr_GL3Window::embeddGLfwWindow()
{
    /*
   * from https://discourse.glfw.org/t/attach-a-glfwwindow-to-windows-window-client-area/882/5:
   */
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
    style |= WS_OVERLAPPED;
    SetWindowLong(glfwHND, GWL_STYLE, style); //set the new style of b
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, true); //place b at (x,y,w,h) in a
    SetParent(glfwHND, hwParentWindow);
    UpdateWindow(glfwHND);
    ShowWindow(glfwHND, SW_SHOW);
    return 1;//everything is OK.
}

int Fr_GL3Window::releaseGLfwWindow()
{
    //todo fixme:
    HWND glfwHND = glfwGetWin32Window(pWindow);
    HWND hwParentWindow = fl_win32_xid(pfltkWindow);
    int result = 0;
    if (hwParentWindow == 0) {
        printf("Failed to get HWND of the window please debugme!!\n");
        return 0;
    }

    DWORD style = GetWindowLong(glfwHND, GWL_STYLE); //get the b style
    style |= (WS_POPUP | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX | WS_SYSMENU | WS_CAPTION); //reset the caption and popup bits
    SetWindowLong(glfwHND, GWL_STYLE, style); //set the new style of b
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, true); //place b at (x,y,w,h) in a
    SetParent(glfwHND, nullptr);
    UpdateWindow(glfwHND);
    ShowWindow(glfwHND, SW_SHOW);
    return 1;//everything is OK.
}

void Fr_GL3Window::deinitializeGlad()
{
    s_GladInitialized = false;
}

void Fr_GL3Window::CreateCameras()
{
    for (int i = 0; i < 6; i++) {
        std::shared_ptr camera_ = std::make_shared<Camera>();   //Shared pointer to the camera,
        //We need to have the transform object to control the camera. Only one child should be allowed TODO FIXME:
        auto camera_trans = std::make_shared<Transform>();
        if (i == 0) {
            camera_trans->AddNode(camera_);
            camera_->SetActive(true);   //Only one camera is defined by default.
                                       //You should activate other cameras if you want another view and deactivate the default.
            camera_trans->Translate(0.6, 0.5, 1.7);
            camera_trans->Rotate(glm::vec3(1, 0,0 ), 180);

        }
        else {
            camera_->SetActive(false);
        }
        camera_trans->AddNode(camera_);
        scene->AddNode(camera_trans);  //Add it to the scene graph, but only active one will render.
        camera_->setCameraType((CameraList)i);   //Depending on the list it should be as the enum defined
        auto manipulator = new Manipulator(); //manipulation for the camera.
        camera_->SetManipulator(std::unique_ptr<Manipulator>(manipulator));
        cameras.push_back(camera_trans);  //Transform with a camera child.
    }
}

int Fr_GL3Window::createGLFWwindow()
{
    //***********************************************************************************************
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    pWindow = glfwCreateWindow(_wGl, _hGl, "LearnOpenGL", NULL, NULL);

    glfwSetWindowUserPointer(pWindow, (void*)pfltkWindow); //allow user data go to the callback //TODO use this with all callbacks
    if (pWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);
    glfwSetFramebufferSizeCallback(pWindow, GLFWCallbackWrapper::framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    s_GladInitialized = true;
    FR::s_GladInitialized = true;
    embeddGLfwWindow();

    //***************************************************

    /**
        Based on the discussion https://stackoverflow.com/questions/7676971/pointing-to-a-function-that-is-a-class-member-glfw-setkeycallback
    */
#define genericCallback(functionName)[](GLFWwindow* window, auto... args) {\
            auto pointer = static_cast<GLFWwindow*>(glfwGetWindowUserPointer(window));\
            if (pointer->functionName) pointer->functionName(pointer, args...);}

    // GLFW callbacks  https://www.glfw.org/docs/3.3/input_guide.html
    glfwSetFramebufferSizeCallback(pWindow, GLFWCallbackWrapper::framebuffer_size_callback);
    glfwSetKeyCallback(pWindow, GLFWCallbackWrapper::keyboard_callback);
    glfwSetCursorPosCallback(pWindow, GLFWCallbackWrapper::cursor_position_callback);
    glfwSetCursorEnterCallback(pWindow, GLFWCallbackWrapper::cursor_enter_callback);
    glfwSetMouseButtonCallback(pWindow, GLFWCallbackWrapper::mouse_button_callback);
    glfwSetScrollCallback(pWindow, GLFWCallbackWrapper::scroll_callback);
    glfwSetJoystickCallback(GLFWCallbackWrapper::joystick_callback);
    return 1;
}

int Fr_GL3Window::updateGLFWWindow()
{
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, true); //place b at (x,y,w,h) in a
    UpdateWindow(glfwHND);
    RedrawWindow(glfwHND, NULL, NULL, RDW_FRAME | RDW_INTERNALPAINT);
    if (s_GladInitialized) {
        glad_glFlush();
    }
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

/**
* This will prepare showing the windows.
* Nothing still be drawn before running the
* application
* You need to use Fr_GL3Window::run () to get
* things running and shown on the screen.
*/

void Fr_GL3Window::show() {
    Fl_Window::show();
    //Create the GLFW Window
    if (pWindow == nullptr) {
        if (createGLFWwindow() != 0) {
            if (s_GladInitialized == true) {
                //glad_glClearColor(1.0, 0.16, 0.18, 1.0);
                //glClear(GL_COLOR_BUFFER_BIT);
                updateGLFWWindow();
            }
        }
    }
}

/**
* Resize both windows. FLTK and GLFW. Be aware that you need to set GLFW size before resizing this
*/
void Fr_GL3Window::resize(int x, int y, int w, int h)
{
    Fl_Window::resize(x, y, w, h);
    float _ratio = float(w * h) / float(Ow * Oh);  /// Calculate ratio of resized of window
    if (s_GladInitialized) {
        if (_ratio != 0)
            resizeGlWindow(_ratio);
    }
    //damage(FL_DAMAGE_ALL);
    //Fl_Window::draw();
}

/**
* Put resizable widget for the whole window
*   TODO: You need to add some more code to allow GLFW to be resizable
*/
void Fr_GL3Window::resizable(Fl_Widget* w)
{
    Fl_Window::resizable(w);
}

/**
* Run the application . This is a replacer of Fl:run.
* We need to make our own since FLTK will not be involved
* in keeping the window visible directly.
* GLFW will keep the whole window visible
* to the time any of them hides or terminates
*
*/
static float countert = 0.0;
int Fr_GL3Window::GLFWrun()
{
    CreateScene();   //Main drawing process.
    glfwSwapInterval(1);
    glfwMakeContextCurrent(pWindow);
    glViewport(0, 0, _wGl, _hGl);

    while (!glfwWindowShouldClose(pWindow))
    {
        //Update FLTK 24 frames/sec
        newTime = glfwGetTime();
        if (oldTime == 0) {
            oldTime = newTime;
        }
        double delta = newTime - oldTime;
        oldTime = newTime;
        fltktimerValue = fltktimerValue + delta;
        if (fltktimerValue >= redrawFPS) {
            fltktimerValue = 0.0;
            redrawFLTKTimer_cb(this);
            Fl::flush();
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(FR_WINGS3D);   ///Background color for the whole scene  - defualt should be wings3D or FreeCAD

        scene->RenderScene();
        if (s_GladInitialized) {
            glCheckFunc(glfwSwapBuffers(pWindow));
            glCheckFunc(glfwPollEvents());
        }
    }
    return 0;
}
/**
PerspectiveCamera

  position 17.463835 -17.463825 13.463827\n
  orientation 0.74290609 0.30772209 0.59447283  1.2171158\n
  nearDistance 0.42925534\n
  farDistance 1761.75\n
  aspectRatio 1\n
  focalDistance 30.248238\n
  heightAngle 0.78539819

  */

std::shared_ptr<Transform> Fr_GL3Window::CreateSun() {
    //TODO: FIXME:
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
    sun->SetActive(true);   //A must to have or the rabbit mesh will be black.
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

void Fr_GL3Window::GLFWCallbackWrapper::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    s_fr_glfwwindow->framebuffer_size_callback(window, width, height);
}

void Fr_GL3Window::GLFWCallbackWrapper::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    s_fr_glfwwindow->keyboard_callback(window, key, scancode, action, mods);
}

void Fr_GL3Window::GLFWCallbackWrapper::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    s_fr_glfwwindow->cursor_position_callback(window, xpos, ypos);
}

void Fr_GL3Window::GLFWCallbackWrapper::cursor_enter_callback(GLFWwindow* window, int entered)
{
    s_fr_glfwwindow->cursor_enter_callback(window, entered);
}

void Fr_GL3Window::GLFWCallbackWrapper::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    s_fr_glfwwindow->mouse_button_callback(window, button, action, mods);
}

void Fr_GL3Window::GLFWCallbackWrapper::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    s_fr_glfwwindow->scroll_callback(window, xoffset, yoffset);
}

void Fr_GL3Window::GLFWCallbackWrapper::joystick_callback(int jid, int events)
{
    s_fr_glfwwindow->joystick_callback(jid, events);
}

void Fr_GL3Window::GLFWCallbackWrapper::setGLFWwindow(Fr_GL3Window* glfwWindow)
{
    GLFWCallbackWrapper::s_fr_glfwwindow = glfwWindow;
}