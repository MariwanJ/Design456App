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

/**
 *
 * Update FLTK callback.
 * This function should replace the need of Fl::run
 * It will be calle
 * \param window
 */


GLuint m_QuadVA, m_QuadVB, m_QuadIB;
bool s_GLFWInitialized;

GLFWwindow* Fr_GL3Window::pWindow = nullptr;

bool Fr_GL3Window::s_GLFWInitialized = false;
bool Fr_GL3Window::s_GladInitialized = false;
Fr_GL3Window* Fr_GL3Window::GLFWCallbackWrapper::s_fr_glfwwindow = nullptr;

static int counter = 0;

Fr_GL3Window* FR::globalP_pWindow = nullptr;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

/**
* Class constructor -
* FIXME: CLEANUP CODE
*/
Scene* Fr_GL3Window::scene = nullptr;
Fr_GL3Window::Fr_GL3Window(int x = 0, int y = 0, int w = 900, int h = 800, std::string l = "GLFW ImGUI Test"):
                                active_camera_(CameraList::PERSPECTIVE), 
                                _x(x), _y(y), _w(w), _h(h), label_(l) {
    FR::globalP_pWindow = this;

    _x = x;
    _y = y;
    _w = w;
    _h = h;

    gl_version_major = 4;
    gl_version_minor = 3;
    glfwSetErrorCallback(error_callback);
    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        //FRTK_CORE_ASSERT(success, "Could not intialize GLFW!");
        s_GLFWInitialized = true;
    }
    //Hint to GLFW  - Window is visible, not decorated and gl version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Fr_GL3Window::flush() {
    glad_glFlush();
}

Fr_GL3Window::Fr_GL3Window()
{
    _x = 0;
    _y = 0;
    _w = 900;
    _h = 800;
    label_ = "GLFW ImGUI Test";
}

//FIXME
Fr_GL3Window::~Fr_GL3Window()
{
}

/**
* Exit application and destroy both windows.
*/
int Fr_GL3Window::exit()
{
    if (pWindow)
        glfwDestroyWindow(pWindow);
    return 0;
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
    //scene->AddNode(bunny());
    scene->AddNode(Grid().CreateGrid());
    vert axis = Axis3D().CreateAxis3D();
    scene->AddNode(axis.Red);
    scene->AddNode(axis.Green);
    scene->AddNode(axis.Blue);
}

void Fr_GL3Window::resizeWindow(int xGl, int yGl, int wGl, int hGl)
{
    //Use this to resize the GLFW window regardless the ratio
    _x = xGl;
    _y = yGl;
    _w = wGl;
    _h = hGl;
}

//TODO : FIXME : Maybe it is not correct???
void Fr_GL3Window::hide()
{
    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(pWindow);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Fr_GL3Window::deinitializeGlad()
{
    s_GladInitialized = false;
}

int Fr_GL3Window::x() const
{
    return _x;
}

int Fr_GL3Window::y() const
{
    return _y;
}

int Fr_GL3Window::w() const
{
    return _w;
}

int Fr_GL3Window::h() const
{
    return _h;
}

const char* Fr_GL3Window::label() const
{
    return label_.c_str();
}

void Fr_GL3Window::label(std::string l)
{
    label_ = l;
}

void Fr_GL3Window::label(const char* l)
{
    label_ = l;
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
int Fr_GL3Window::renderimGUI(){
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
 {
        if(imgui_LeftPanel()<0)
            return -1;
        if(imgui_TopPannel()<0)
            return -1;
        if(imgui_NavigationBox())
            return -1;
        if(imgui_ViewPort())
           return -1;

     //glfwSwapBuffers(pWindow);

 }
 return 1;

}
int Fr_GL3Window::imgui_LeftPanel()
{
    return 0;
}
int Fr_GL3Window::imgui_TopPannel()
{
    ImGui::ShowDemoWindow();
    return 0;
}
int Fr_GL3Window::imgui_NavigationBox()
{
        //Demo code fix me
    
    static float f = 0.0f;
    static int counter = 0;
    bool show_demo_window = true;
    bool show_another_window = false;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    return 0;
}
int Fr_GL3Window::imgui_ViewPort()
{   //Demo code fix me
    ImGui::Begin("ViewPort");
    ImGui::Text("View Port");               // Display some text (you can use a format strings too)
    //scene->RenderScene();
    ImGui::End(); 

    return 0;
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
    pWindow = glfwCreateWindow(_w, _h, label_.c_str(), NULL, NULL);

    if (pWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    s_GladInitialized = true;
    FR::s_GladInitialized = true;
    // GLFW callbacks  https://www.glfw.org/docs/3.3/input_guide.html
    glfwSetFramebufferSizeCallback(pWindow, GLFWCallbackWrapper::framebuffer_size_callback);
    glfwSetKeyCallback(pWindow, GLFWCallbackWrapper::keyboard_callback);
    glfwSetCursorPosCallback(pWindow, GLFWCallbackWrapper::cursor_position_callback);
    glfwSetCursorEnterCallback(pWindow, GLFWCallbackWrapper::cursor_enter_callback);
    glfwSetMouseButtonCallback(pWindow, GLFWCallbackWrapper::mouse_button_callback);
    glfwSetScrollCallback(pWindow, GLFWCallbackWrapper::scroll_callback);
    glfwSetJoystickCallback(GLFWCallbackWrapper::joystick_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();
        // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
    return 1;
}


void Fr_GL3Window::resize(int x, int y, int w, int h)
{
}

void Fr_GL3Window::show() {
    if (createGLFWwindow() != 0) {
            if (s_GladInitialized == true) {
            //                       TODO: DO WE NEED THIS? I remove it for now
            }
        }
}

int Fr_GL3Window::GLFWrun()
{
    CreateScene();   //Main drawing process.
    glfwSwapInterval(1);
    glfwMakeContextCurrent(pWindow);
    glViewport(0, 0, _w, _h);
    clear_color = ImVec4(FR_WINGS3D); //ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(FR_WINGS3D);   ///Background color for the whole scene  - defualt should be wings3D or FreeCAD
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderimGUI();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(pWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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