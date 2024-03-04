//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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
namespace FR {
    Fr_GL3Window* Fr_enttScene::linkToglfw = nullptr;
    GLuint m_QuadVA, m_QuadVB, m_QuadIB;

    bool Fr_GL3Window::s_GLFWInitialized = false;
    bool Fr_GL3Window::s_GladInitialized = false;
    Fr_GL3Window* Fr_GL3Window::GLFWCallbackWrapper::s_fr_glfwwindow = nullptr;

    static int counter = 0;

    Fr_GL3Window* Fr_GL3Window::s_Fr_GLFWwindow = nullptr;
    eventData Fr_GL3Window::m_GLFWevents = { -1,-1,-1,-1,-1 };

    glfwMouseEvent Fr_GL3Window::mouseEvent = { 0,0,0,0,false,0 };

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
        WidgWindow(NULL), MainWinCursor(NULL), activeScene(nullptr),
        _x(x), _y(y), _w(w), _h(h), label_(l), showOpenDialog(false) {
        s_Fr_GLFWwindow = this;
        _x = x;
        _y = y;
        _w = w;
        _h = h;
        mouseDefaults.MouseScrollScale = 1.5f;
        mouseDefaults.MouseXYScale = 1.1f;
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
        //WidgWindow->linkToMainWindow = (Fr_GL3Window*)this;             ----------------------------------------------->                                FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!2024-02-19
        // WidgWindow->setParentlink(this);     ----------------------------------------------->                                FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!2024-02-19
        radiusXYZ = 0.0f;
        phi = theta = 0.f;
        runCode = true;

#if 1 //just for debug purpose
        mousePos = { 0,0 };
#endif
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
        activeScene = std::make_shared<Fr_enttScene>();
        activeScene->linkToglfw = this;
        //       TODO CHECK ME !!
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
        activeScene->active_camera_ = _type;
        for (int i = 0; i < MAX_CAMERAS; i++) {
            (activeScene->m_cameraList[i])->isActive(false);
        }
        (activeScene->m_cameraList[(int)activeScene->active_camera_])->isActive(true);
    }

    CameraList Fr_GL3Window::getCameraType()
    {
        return activeScene->active_camera_;
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
        activeScene->setupScene();
        glfwGetFramebufferSize(pWindow, &_w, &_h);
        glViewport(_x, _y, _w, _h);

        userData_ data;
        while (!glfwWindowShouldClose(pWindow))
        {
            layers_[0]->StartLayer();   //Default layer. This should always be there.
            glClearColor(FR_WINGS3D);   ///Background color for the whole scene  - defualt should be wings3D or FreeCAD
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            renderimGUI(data);

            layers_[0]->EndLayer();   //Default layer. This should always be there.       
            glCheckFunc(glfwPollEvents());
            glCheckFunc(glfwSwapBuffers(pWindow));
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(pWindow);
        return 0;
    }
}