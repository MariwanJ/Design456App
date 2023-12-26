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
#include<fr_mesh.h>        
#include<halfEdge/fr_new_mesh.h>
#include<fr_modelnodeShader.h>
//End remove me later

GLuint m_QuadVA, m_QuadVB, m_QuadIB;

bool Fr_GL3Window::s_GLFWInitialized = false;
bool Fr_GL3Window::s_GladInitialized = false;
Fr_GL3Window* Fr_GL3Window::GLFWCallbackWrapper::s_fr_glfwwindow = nullptr;

static int counter = 0;

Fr_GL3Window* Fr_GL3Window::s_Fr_GLFWwindow = nullptr;
eventData Fr_GL3Window::m_GLFWevents = { -1,-1,-1,-1,-1 };

glfwMouseEvent Fr_GL3Window::mouseEvent = {0,0,0,0,false,0};

Scene* Fr_GL3Window::scene = nullptr;
bool Fr_GL3Window::MouseOnce = true;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


/**
* Class constructor -
* FIXME: CLEANUP CODE
*/

Fr_GL3Window::Fr_GL3Window(int x = 0, int y = 0, int w = 900, int h = 800, std::string l = "GLFW ImGUI Test") :
    WidgWindow(NULL),
    active_camera_(CameraList::PERSPECTIVE),
    _x(x), _y(y), _w(w), _h(h), label_(l), showOpenDialog(false) {
    s_Fr_GLFWwindow = this;
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    mouseDefaults.MouseScrollScale = 1.2;
    mouseDefaults.MouseXYScale = 0.0001f;
    phi = -90.0f;
    theta = 0;
    gl_version_major = 4;
    gl_version_minor = 6;
    glfwSetErrorCallback(error_callback);
    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        //FRTK_CORE_ASSERT(success, "Could not initialize GLFW!");
        s_GLFWInitialized = true;
    }
    //Hint to GLFW  - Window is visible, not decorated and gl version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    Fr_GL3Window::GLFWCallbackWrapper::setGLFWwindow(this);
    WidgWindow = std::make_shared<FR::Fr_Window>(); //Create FR_WINDOW that keeps the widget system
    WidgWindow->linkToMainWindow = this;
    radiusXYZ = 0;
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
    s_Fr_GLFWwindow = this;
    WidgWindow = std::make_shared<FR::Fr_Window>(); //Create FR_WINDOW that keeps the widget system
    WidgWindow->linkToMainWindow = this;
}

Fr_GL3Window* Fr_GL3Window::getfr_Gl3Window()
{
    return s_Fr_GLFWwindow;
}

//FIXME
Fr_GL3Window::~Fr_GL3Window()
{
}

void Fr_GL3Window::addLayer(std::shared_ptr<Fr_ImGuiLayer> layer)
{
    layers_.push_back(layer);
}

void Fr_GL3Window::removeLayer(std::shared_ptr<Fr_ImGuiLayer> layer)
{
    layers_.erase(find(layers_.begin(), layers_.end(), layer));
}

/**
* Exit application and destroy both windows.
*/
int Fr_GL3Window::Exit()
{
    if (pWindow)
    {
        glfwSetWindowShouldClose(pWindow, true);
        glfwPollEvents();
        return 0;
    }
    return 0;
}

GLFWwindow* Fr_GL3Window::getCurrentGLWindow()
{
    return pWindow;
}
/**
 * Main Scene creation. It creates the cameras, Grid, Axis, and Navigation box (Not implemented yet) 
 * 
 */

#include<ThreeDWidgets/fr_line_widget.h> ///this is a test TODO : REMOVE ME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
void Fr_GL3Window::CreateScene()
{
    scene = new Scene();//Save a link to the windows also.
    scene->linkToglfw = pWindow;

    CreateCameras();
    setCameraType(CameraList::PERSPECTIVE);

    /*
      * Add here the nodes - Grid, and XYZ axis
      */
    scene->AddNode(WidgWindow);
    scene->AddNode(CreateSunTop());
    scene->AddNode(CreateSunBottom());
    tempBu = bunny();
    auto dd = bunny();
    dd->Translate(10.f, 30.f, 20.f);
    scene->AddNode(Grid().CreateGrid());
    vert axis = Axis3D().CreateAxis3D();
    scene->AddNode(axis.Red);
    scene->AddNode(axis.Green);
    scene->AddNode(axis.Blue);
    scene->AddNode(tempBu);
    scene->AddNode(dd);

    std::shared_ptr<std::vector<float>> vert = std::make_shared<std::vector<float>>(std::initializer_list<float>{10.f, 10.f, 0.f, 100.f, 100.f, 100.f});
    std::shared_ptr < std::vector<unsigned int>> ind = std::make_shared<std::vector<unsigned int>>(std::initializer_list<unsigned int>{0,1});
    std::shared_ptr<FR::Fr_Line_Widget> line = std::make_shared<FR::Fr_Line_Widget>(glm::vec3(0.0f, 0.0f, 0.0f), vert, ind,"");
    WidgWindow->addWidget(line);

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

ImVec4 Fr_GL3Window::getPortViewDimensions()
{
    return  PortViewDimensions;
}

void Fr_GL3Window::setPortViewDimension(ImVec4 value)
{
    PortViewDimensions = value;
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
/**
 * Set active camera which affects how setup works.
 *
 * \param _type Camera type which is written in CameraList enum
 */
void Fr_GL3Window::setCameraType(CameraList _type)
{
    active_camera_ = _type;
    for (int i = 0; i < MAX_CAMERAS; i++) {
        (cameraList[i])->SetActive(false);
    }
    (cameraList[(int)active_camera_])->SetActive(true);
}

CameraList Fr_GL3Window::getCameraType()
{
    return active_camera_;
}

/**
 *
 * Create a list of cameras that will be later used using GUI buttons.
 *
 */
void Fr_GL3Window::CreateCameras()
{
    for (int i = 0; i < MAX_CAMERAS; i++) {
        auto camera_ = std::make_shared < Camera>();   //Shared pointer to the created camera,
        //By default no camera is active, developer MUST define one after creating cameras
        camera_->SetActive(false);
        cameraList.push_back(camera_);
        scene->AddNode(camera_);  //Add it to the scene graph, but only active one will render.
        camera_->setType((CameraList)i);   //Depending on the list it should be as the enum defined
        camera_->setupCameraHomeValues();

        switch (i) {
            //TODO: FIXME: If you create more than 6, you should add it here
        case 0: {
            /*Normal view PERSPECTIVE, HOME
                    position 17.463835 -17.463825 13.463827\n
                    orientation 0.74290609 0.30772209 0.59447283  1.2171158\n
                    nearDistance 0.42925534\n
                    farDistance 1761.75\n
                    aspectRatio 1\n
                    focalDistance 30.248238\n
                    heightAngle 0.78539819\n\n}\n'
            */
            camera_->Rotate(glm::vec3(0.7429f, 0.307f, 0.594f), -69.7f);
        }break;
        case 1: {
            //ORTHOGRAPHIC

            camera_->Rotate(glm::vec3(0.74290609f, 0.30772209f, 0.59447283f), 69.7f);
        }break;
        case 2: {
            /*TOP
             position 15.337841 10.960548 102.60384\n
             orientation 0 0 1  0\n
             nearDistance 102.50124\n
             farDistance 102.70644\n
             aspectRatio 1\n
             focalDistance 100\n
             height 44.932899\n\n}\n'
            */
            camera_->Rotate(glm::vec3(0.0f, 0.0, 1.0f), 0);
        }break;
        case 3: {
            /*Bottom
             position 10.531155 7.5401545 -97.396126\n
             orientation -0.99999994 1.4210855e-014 9.4830476e-008  3.1415935\n
             nearDistance 97.298668\n
             farDistance 97.493576\n
             aspectRatio 1\n
             focalDistance 100\n
             height 44.932903\n\n}\n'
            */
            camera_->Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 180);
        }break;
        case 4: {
            /**
             *  FRONT
              position 28.817665 -89.039444 2.6038942\n
              orientation -1 4.214686e-007 8.4293717e-008  4.7123895\n
              nearDistance 34.005363\n
              farDistance 144.1835\n
              aspectRatio 1\n
              focalDistance 100\n
              height 44.932899\n\n}\n'
                     *
             */
            camera_->Rotate(glm::vec3(-1.0f, 0, 0), 270.0f);
        }break;
        case 5: {
            /*REAR
                position 15.337867 110.96054 2.6038241\n
                orientation 1.4901161e-008 - 0.70710683 - 0.70710671  3.141593\n
                nearDistance 55.904575\n
                farDistance 166.1265\n
                aspectRatio 1\n
                focalDistance 100\n
                height 44.932899\n\n}\n'
                */
            camera_->Rotate(glm::vec3(0.f, -0.70710683, -0.70710671f), 270.0f);
        }break;
        case 6: {
            /*
            RIGHT
                position 115.33784 10.960509 2.6038659\n
                orientation - 0.57735032 - 0.57735026 - 0.5773502  4.1887908\n
                nearDistance 60.277466\n
                farDistance 170.50819\n
                aspectRatio 1\n
                focalDistance 100\n
                height 44.932899\n\n
                */
            camera_->Rotate(glm::vec3(-0.577f, -0.577f, -0.577f), 240.f);
        }break;

        case 7: {
            /*LEFT
                position - 71.182274 10.960546 2.6038406\n
                orientation 0.57735014 - 0.5773505 - 0.5773502  2.0943947\n
                nearDistance 16.166088\n
                farDistance 126.30847\n
                aspectRatio 1\n
                focalDistance 100\n
                height 44.932899\n\n}\n'
                */
            camera_->Rotate(glm::vec3(0.57f, -0.57f, -0.57f), 270.0f);
        }break;
        }
    }
}

int Fr_GL3Window::createGLFWwindow()
{
    //***********************************************************************************************
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

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
    glfwSwapInterval(1);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    s_GladInitialized = true;
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
    userData_ data;
    glViewport(0, 0, _w, _h);

    clear_color = ImVec4(FR_WINGS3D); //ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    sceneBuffer = std::make_shared<Fr_TextureFrameBuffer>(w(), h());        //Our draws will be on this buffer, which then drawn inside portview in ImGui

    /**
     *
     * For the layers, We will make :
     *  Main layer which has the dockspace and all other GUI parts and will be default visible object layer
     */
    std::shared_ptr<Fr_ImGuiLayer> mlayer = std::make_shared<Fr_ImGuiLayer>();
    layers_.push_back(mlayer);
    layers_[0]->createLayer();
    CreateScene();   //Main drawing process.
    glfwGetFramebufferSize(pWindow, &_w, &_h);
    glViewport(_x, _y, _w, _h);
    while (!glfwWindowShouldClose(pWindow))
    {
        layers_[0]->StartLayer();   //Default layer. This should always be there.
        glClearColor(FR_WINGS3D);   ///Background color for the whole scene  - defualt should be wings3D or FreeCAD
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        //Render GLFW stuff or Our 3D drawing
        renderimGUI(data);
        // Rendering IMGUI
        layers_[0]->EndLayer();
        glCheckFunc(glfwPollEvents());
        glCheckFunc(glfwSwapBuffers(pWindow));
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(pWindow);
    return 0;
}

std::shared_ptr<Transform> Fr_GL3Window::CreateSunTop() {
    //TODO: FIXME:
    auto sun_ = std::make_shared<Transform>();
    sun_->Translate(0.0f, 0.0f, 0.f);
    sun = std::make_shared<Light>();
    sun->SetPosition(0.0f, 0.0f, 1000.0f);
    sun->SetDiffuse(0.25f, 0.25f, 0.25f);
    sun->SetAmbient(0.2f, 0.2f, 0.2f);
    sun->EnableShadowMap(glm::vec3(0, 0, 1), glm::vec3(0, 0, 4), glm::ortho<float>(-10, 10, -10, 10, 100, 114));
    sun_->AddNode(sun);
    sun->SetActive(true);   //A must to have otherwise everything is black.
    sunT = std::move(sun_);
    return sunT;
}
std::shared_ptr<Transform> Fr_GL3Window::CreateSunBottom() {
    //TODO: FIXME:
    auto sun_ = std::make_shared<Transform>();
    sun_->Translate(-100.0f, -100.f, -300.0f);
    sun = std::make_shared<Light>();
    sun->SetPosition(0.0f, 0.0f, 0.0f);
    sun->SetDiffuse(0.5f, 0.5f, 0.5f);
    sun->SetAmbient(0.2f, 0.2f, 0.2f);
    //sun->EnableShadowMap(glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), glm::ortho<float>(-50, 50, -50, 50, 400, 600));
    sun_->AddNode(sun);
    sun->SetActive(false);   //A must to have otherwise everything is black.
    sunT = std::move(sun_);
    return sunT;
}