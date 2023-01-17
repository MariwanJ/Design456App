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
    win->exit();
}

GLFWwindow* Fr_GL3Window::pWindow = nullptr;


bool Fr_GL3Window::s_GLFWInitialized = false;
bool Fr_GL3Window::s_GladInitialized = false;

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
    Fl::repeat_timeout(redrawFPS, redrawFLTKTimer_cb, (void*)win);
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
Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h, const char* l) :Fl_Double_Window(x, y, w, h, l),
                                                                        overlay(false),
                                                                        curr_camera(Cam1){

    //Default size is the size of the FLTK window
    FR::globalP_pWindow = this;

    _xGl = x;
    _yGl = y;
    _wGl = w ;
    _hGl = h ;
    gl_version_major = 3;
    gl_version_minor = 0;
    glfwSetErrorCallback(error_callback);




    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        //FRTK_CORE_ASSERT(success, "Could not intialize GLFW!");
        //glfwSetErrorCallback(GLFWErrorCallback);
        s_GLFWInitialized = true;
    }
    //Hint to GLFW  - Window is visible, not decorated and gl version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major) ;
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
    updateGLFWWindow();
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
    glfwDestroyWindow(pWindow);
    pfltkWindow->~Fl_Double_Window();
    return 1;
}



#include<Mesh.h>
#include<ToonShaderNode.h>


static std::shared_ptr<Transform> CreateRoad() {
    auto floor = std::make_shared<Transform>();

    auto quad = std::make_shared<Mesh>("E:/Projects/Design456App/frtk/src/data/quad.msh");

    auto grass_t = std::make_shared<Transform>();
    grass_t->Scale(1000, 0, 1000);
    floor->AddNode(grass_t);

    auto grass = std::make_shared<ToonShaderNode>(0xBADA5F);
    grass->SetMesh(quad);
    grass_t->AddNode(grass);

    auto road_t = std::make_shared<Transform>();
    road_t->Scale(1000, 1, 10);
    road_t->Translate(0, 0.001, 0);
    floor->AddNode(road_t);

    auto road = std::make_shared<ToonShaderNode>(0x111111);
    road->SetMesh(quad);
    road_t->AddNode(road);

    auto strip = std::make_shared<ToonShaderNode>(0xEEEE11);
    strip->SetMesh(quad);

    for (int i = 0; i < 125; ++i) {
        auto strip_t = std::make_shared<Transform>();
        strip_t->Translate(i * 8 - 500, 0.002, 0);
        strip_t->Scale(2.5, 1, 0.2);
        floor->AddNode(strip_t);
        strip_t->AddNode(strip);
    }

    return floor;
}

static std::shared_ptr<Transform> CreateShip() {
    auto ship_t = std::make_shared<Transform>();
    ship_t->Translate(-10, 10, 0);
    ship_t->Scale(10, 10, 10);
    ship_t->Rotate(90, 0, -1, 0);
    ship_t->Rotate(90, -1, 0, 0);

    auto ship = std::make_shared<ToonShaderNode>(0x444444);
    ship->SetMesh("E:/Projects/try things/Scene-Graph-222_Important/src/data/klingon_starship.off");
    ship_t->AddNode(ship);

    return ship_t;
}

static std::shared_ptr<ToonShaderNode> CreateJeepItem(
    std::shared_ptr<Transform> jeep, const std::string& name,
    unsigned int color) {
    auto item = std::make_shared<ToonShaderNode>(color, 0.009);
    item->SetMesh("E:/Projects/try things/Scene-Graph-222_Important/src/data/jeep_" + name + ".msh");
    jeep->AddNode(item);
    return item;
}


static std::shared_ptr<Transform> CreateJeep() {
    auto jeep = std::make_shared<Transform>();
    jeep->Rotate(90, -1, 0, 0);

    // Create static stuff
    CreateJeepItem(jeep, "body", 0xD1943F);
    CreateJeepItem(jeep, "lanterns", 0x991111);
    CreateJeepItem(jeep, "handle", 0xAAAAEE);
    CreateJeepItem(jeep, "panel", 0x222222);
    CreateJeepItem(jeep, "seat", 0x705A34);
    CreateJeepItem(jeep, "windshieldcleaner", 0x222222);
    auto windshield = CreateJeepItem(jeep, "windshield", 0xBBBBEE);
    windshield->SetOpacity(0.3);

    // Create driver
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0.9, -0.6, 1.2);
    bunny_t->Scale(0.6, 0.6, 0.6);
    bunny_t->Rotate(90, 1, 0, 0);
    bunny_t->Rotate(90, 0, 1, 0);
    jeep->AddNode(bunny_t);

    auto bunny = std::make_shared<ToonShaderNode>(0xAA55AA, 0.02);
    bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/try things/Scene-Graph-222_Important/src/data/bunny.off"));
    bunny_t->AddNode(bunny);

    // Create right wheel
    auto rightwheel = std::make_shared<Transform>();
    rightwheel->Translate(-2.5, 0.644, -0.438);
    auto tire = CreateJeepItem(rightwheel, "tire", 0x444444);
    auto hubcap = CreateJeepItem(rightwheel, "hubcap", 0xAAAAAA);

    // Create front right wheel
    auto frontrightwheel_speed = std::make_shared<Transform>();
    frontrightwheel_speed->AddNode(rightwheel);

    auto frontrightwheel_direction = std::make_shared<Transform>();
    frontrightwheel_direction->AddNode(frontrightwheel_speed);

    auto frontrightwheel = std::make_shared<Transform>();
    frontrightwheel->AddNode(frontrightwheel_direction);
    frontrightwheel->Translate(2.5, -0.644, 0.438);
    jeep->AddNode(frontrightwheel);

    // Create back right wheel
    auto backrightwheel_speed = std::make_shared<Transform>();
    backrightwheel_speed->AddNode(rightwheel);

    auto backrightwheel = std::make_shared<Transform>();
    backrightwheel->AddNode(backrightwheel_speed);
    backrightwheel->Translate(0, -0.644, 0.438);
    jeep->AddNode(backrightwheel);

    // Create left wheel
    auto leftwheel = std::make_shared<Transform>();
    leftwheel->Rotate(180, 0, 0, 1);
    leftwheel->AddNode(rightwheel);

    // Create front left wheel
    auto frontleftwheel_speed = std::make_shared<Transform>();
    frontleftwheel_speed->AddNode(leftwheel);

    auto frontleftwheel_direction = std::make_shared<Transform>();
    frontleftwheel_direction->AddNode(frontleftwheel_speed);

    auto frontleftwheel = std::make_shared<Transform>();
    frontleftwheel->AddNode(frontleftwheel_direction);
    frontleftwheel->Translate(2.5, 0.644, 0.438);
    jeep->AddNode(frontleftwheel);

    // Create back left wheel
    auto backleftwheel_speed = std::make_shared<Transform>();
    backleftwheel_speed->AddNode(leftwheel);

    auto backleftwheel = std::make_shared<Transform>();
    backleftwheel->AddNode(backleftwheel_speed);
    backleftwheel->Translate(0, 0.644, 0.438);
    jeep->AddNode(backleftwheel);

    // Create lights
    auto rightlight = std::make_shared<Transform>();
    auto rightlight_model = CreateJeepItem(rightlight, "light", 0xEEEEEE);
    rightlight_model->SetOpacity(0.3);
    jeep->AddNode(rightlight);

    auto rightlight_spot = std::make_shared<Light>();
    rightlight_spot->SetActive(false);
    rightlight_spot->SetPosition(2.956, -0.514, 1.074);
    rightlight_spot->SetupSpot(1, 0, -0.1, 45, 16);
    rightlight_spot->SetDiffuse(0, 0, 0);
    rightlight_spot->SetAmbient(0.42, 0.42, 0.42);
    rightlight_spot->SetAttenuation(1, 0.002, 0);
    rightlight->AddNode(rightlight_spot);
    //jeep_light = rightlight_spot.get();

    auto leftlight = std::make_shared<Transform>();
    leftlight->Translate(0, 1.028, 0);
    leftlight->AddNode(rightlight);
    jeep->AddNode(leftlight);

    // Create steering wheel
    auto steering_wheel_centered = std::make_shared<Transform>();
    steering_wheel_centered->Translate(-1.111, -0.495, -1.372);
    CreateJeepItem(steering_wheel_centered, "steeringwheel", 0x222222);

    auto steering_wheel_engine = std::make_shared<Transform>();
    steering_wheel_engine->AddNode(steering_wheel_centered);

    auto steering_wheel = std::make_shared<Transform>();
    steering_wheel->AddNode(steering_wheel_engine);
    steering_wheel->Translate(1.111, 0.495, 1.372);
    jeep->AddNode(steering_wheel);

    // Creates the engine
    /*engine = new Engine(jeep, frontleftwheel_direction,
        frontrightwheel_direction, frontleftwheel_speed,
        frontrightwheel_speed, backleftwheel_speed, backrightwheel_speed,
        steering_wheel_engine);*/

    // Creates the driver camera
    auto drivercamera_t = std::make_shared<Transform>();
    drivercamera_t->Translate(0.6, 0.5, 1.7);
    drivercamera_t->Rotate(90, 1, 0, 0);
    jeep->AddNode(drivercamera_t);

    auto drivercamera = FR::globalP_pWindow->CreateCamera(drivercamera_t.get(), FR::globalP_pWindow->cameras.size());
    drivercamera->SetActive(true);
    drivercamera->SetEye(0, 0, 0);
    drivercamera->SetCenter(1, 0, 0);
    drivercamera->SetUp(0, 1, 0);

    // Creates the 3rd person camera
    auto jeepcamera_t = std::make_shared<Transform>();
    jeepcamera_t->Rotate(90, 1, 0, 0);
    jeep->AddNode(jeepcamera_t);

    auto jeepcamera = FR::globalP_pWindow->CreateCamera(jeepcamera_t.get(), FR::globalP_pWindow->cameras.size());
    FR::globalP_pWindow->cameras[FR::globalP_pWindow->cameras.size()-1].manipulator->SetReferencePoint(1, 1, 0);
    jeepcamera->SetEye(-6, 2, 0);
    jeepcamera->SetCenter(1, 1, 0);
    jeepcamera->SetUp(0, 1, 0);

    return jeep;
}



void Fr_GL3Window::CreateScene()
{
    //static void CreateScene() {
    scene = new Scene();
    scene->SetBackgroud(0.69, 0.95, 1.00);
    auto camera = CreateCamera(scene, Cam1);

    camera->SetEye(20, 5, 20);
    camera->SetCenter(0.5, 0.5, 0);
    camera->SetUp(0, 1, 0);

    scene->AddNode(CreateSun());
    scene->AddNode(CreateRoad());
    scene->AddNode(CreateShip());
    scene->AddNode(CreateJeep());
    scene->AddNode(CreateJeep());
}
//TODO FIXME
void Fr_GL3Window::draw() {
    if (overlay) {
        Fl_Double_Window::draw();
        updateGLFWWindow();
        //FRTK_CORE_INFO("[DRAW BOTH] {0}");
        printf("overlay%i\n", counter);
        counter++;
    }
    else {
        Fl_Double_Window::draw();
        updateGLFWWindow();
        // printf("not overlay%i\n", counter);
        counter++;
    }
    Fl::flush();
}
//TODO FIXME: Do we need this?
void Fr_GL3Window::reset() {
    shaderProgram = 0;
}
/**
*Resize only the GLFW Window.
*/
void Fr_GL3Window::resizeGlWindow(int xGl, int yGl, int wGl, int hGl)
{
    _xGl = xGl;
    _yGl = yGl;
    _wGl = wGl;
    _hGl = hGl;
    // TODO Should fixme
    updateGLFWWindow();
}

int Fr_GL3Window::handle(int event) {
    //gladEvents(event);
    return Fl_Double_Window::handle(event);
}

int Fr_GL3Window::glfw_handle(int evenet)
{
    return 0;
}

void Fr_GL3Window::hide()
{
    glfwMakeContextCurrent(nullptr);
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
    style |= (WS_POPUP | WS_MAXIMIZEBOX| WS_MINIMIZEBOX  | WS_SIZEBOX | WS_SYSMENU| WS_CAPTION); //reset the caption and popup bits
    SetWindowLong(glfwHND, GWL_STYLE, style); //set the new style of b
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, true); //place b at (x,y,w,h) in a
    SetParent(glfwHND, nullptr);
    UpdateWindow(glfwHND);
    ShowWindow(glfwHND, SW_SHOW);
    return 1;//everything is OK.

}

int Fr_GL3Window::createGLFWwindow()
{

    int result = 0;

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
    GLFWwindow* window = glfwCreateWindow(_wGl, _hGl, "LearnOpenGL", NULL, NULL);

    pWindow = window;
    glfwSetWindowUserPointer(window, (void*)pfltkWindow); //allow user data go to the callback //TODO use this with all callbacks
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertices), TriangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    pWindow = window;



    // render loop


   //embeddGLfwWindow();

    //***************************************************

    //glViewport(_xGl, _yGl, _wGl, _hGl);

    // GLFW callbacks  https://www.glfw.org/docs/3.3/input_guide.html
    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
    glfwSetKeyCallback(pWindow, keyboard_callback);
    glfwSetCursorPosCallback(pWindow, cursor_position_callback);
    glfwSetCursorEnterCallback(pWindow, cursor_enter_callback);
    glfwSetMouseButtonCallback(pWindow, mouse_button_callback);
    glfwSetScrollCallback(pWindow, scroll_callback);
    //glfwSetJoystickCallback(joystick_callback);
    result = 1;

    return result;
}

int Fr_GL3Window::updateGLFWWindow()
{
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
    Fl_Double_Window::show();
    //Create the GLFW Window
    if (pWindow==nullptr){
        if (createGLFWwindow() != 0) {
            if (s_GladInitialized == true) {
                glad_glClearColor(1.0, 0.16, 0.18, 1.0);
               // updateGLFWWindow();
                glClear(GL_COLOR_BUFFER_BIT);
            }
        }
    }
}
//TODO FIXME:
void Fr_GL3Window::gladEvents(int events)
{
     updateGLFWWindow();
}
/**
* Resize both windows. FLTK and GLFW. Be aware that you need to set GLFW size before resizing this
*/
void Fr_GL3Window::resize(int x, int y, int w, int h)
{
    Fl_Double_Window::resize(x, y, w, h);
    if (s_GladInitialized) {
        printf("x=%i y=%i w=%i h=%i\n", x, y, w, h);
        resizeGlWindow(_xGl, _yGl, _wGl, _hGl);
        glViewport(_xGl, _yGl, _wGl, _hGl);
    }
    damage(FL_DAMAGE_ALL);
    Fl_Double_Window::draw();
}

/**
* Put resizable widget for the whole window
*   TODO: You need to add some more code to allow GLFW to be resizable
*/
void Fr_GL3Window::resizable(Fl_Widget* w)
{
    Fl_Double_Window::resizable(w);
}
/**
* Run the application . This is a replacer of Fl:run.
* We need to make our own since FLTK will not be involved
* in keeping the window visible directly.
* GLFW will keep the whole window visible
* to the time any of them hides or terminates
*
*/
int Fr_GL3Window::GLFWrun()
{
    //TODO DOSENT WORK .. WHY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Fl::add_timeout(1, redrawFLTKTimer_cb, pfltkWindow);       // 24fps timer
    //Fl::wait(1);
    //shaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);
    CreateScene();
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(pWindow))
    {
        //Update FLTK 24 frames/sec
        newTime = glfwGetTime();
        if (oldTime == 0) {
            oldTime = newTime;
        }

        //glUseProgram(shaderProgram);
        double delta = newTime - oldTime;
        oldTime = newTime;
        fltktimerValue = fltktimerValue + delta;
        if (fltktimerValue >= redrawFPS){
            fltktimerValue = 0.0;
            redrawFLTKTimer_cb(this);
        }

        // render
        scene->RenderScene();
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
        //glad_glFlush();
    }
    return 0;
}
std::shared_ptr<Camera> Fr_GL3Window::CreateCamera(Group* parent, int cameraId)
{
        camera = std::make_shared<Camera>();
        camera->SetPerspective(40, 0.5, 50);
        camera->SetActive(false);
        parent->AddNode(camera);
        manipulator = new Manipulator();
        camera->SetManipulator(std::unique_ptr<Manipulator>(manipulator));

        cam newCam;
        newCam.camera = camera.get();
        newCam.manipulator = manipulator;
        cameras.push_back(newCam);
        return camera;
}


std::shared_ptr<Transform> Fr_GL3Window::CreateSun() {
    sun = new Transform();
    auto sun_height = std::make_shared<Transform>();
    sun_height->Translate(30, 500, 30);
    sun->AddNode(sun_height);

    auto light = std::make_shared<Light>();
    light->SetPosition(0, 0, 0);
    light->SetDiffuse(0.5, 0.5, 0.5);
    light->SetAmbient(0.4, 0.4, 0.4);
    light->EnableShadowMap(glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), glm::ortho<float>(-50, 50, -50, 50, 400, 600));
    sun_height->AddNode(light);

    return std::shared_ptr<Transform>(sun);
}
void Fr_GL3Window::setOpenGLWinowSize(int xGL, int yGL, int wGL, int hGL)
{
    _xGl = xGL;
    _yGl = yGL;
    _wGl = wGL;
    _hGl = hGL;
}
Fr_GL3Window::Fr_GL3Window(int w, int h, const char* l) :Fl_Double_Window(0, 0, w, h, l) {}
Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h) : Fl_Double_Window(x, y, w, h, "TestOpenGl") {}
Fr_GL3Window::Fr_GL3Window(int w, int h) : Fl_Double_Window(0, 0, w, h, "TestOpenGl") {}