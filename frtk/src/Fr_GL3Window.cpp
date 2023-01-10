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
#define border 0
#define redrawFPS  1.0/24.0  // (24 Frames per sec)

float Fr_GL3Window::fltktimerValue = 0.0;

/*********************************************/

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Fl_Double_Window* pfltkWindow= (Fl_Double_Window*)glfwGetWindowUserPointer(window);
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

Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h, const char* l) :Fl_Double_Window(x, y, w, h, l), overlay(false) {
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
    gl_version_major = 3;
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

void Fr_GL3Window::flush() {
    updateGLFWWindow();
    Fl::flush();
}
Fr_GL3Window::~Fr_GL3Window()
{
    ///Fl_Double_Window::hide();
    //glfwDestroyWindow(pWindow);
    //glfwTerminate();
    //glfwDestroyWindow(pWindow);
}

int Fr_GL3Window::exit()
{
    glfwDestroyWindow(pWindow);
    pfltkWindow->~Fl_Double_Window();
    return 1;
}

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

void Fr_GL3Window::reset() {
    shaderProgram = 0;
}

void Fr_GL3Window::resizeGlWindow(int _xG, int _yG, int _wG, int _hG)
{
    /*/
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
    MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, true); //place b at (x,y,w,h) in a
    */
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

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f , 0.0f, // right
        0.0f,  0.5f , 0.0f  // top
    };



    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    embeddGLfwWindow();
    
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
#include <fr_widgets/fr_basic_shapes.h>
int Fr_GL3Window::updateGLFWWindow()
{
    if (s_GladInitialized) {
        glad_glFlush();
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
    Fl_Double_Window::show();
    //Create the GLFW Window
    if (pWindow==nullptr){
        if (createGLFWwindow() != 0) {
            if (s_GladInitialized == true) {
                glad_glClearColor(1.0, 0.16, 0.18, 1.0);
                updateGLFWWindow();
                glfwSwapInterval(1);
                glClear(GL_COLOR_BUFFER_BIT);
            }
        }
    }
}

void Fr_GL3Window::gladEvents(int events)
{
     updateGLFWWindow();
}

void Fr_GL3Window::resize(int x, int y, int w, int h)
{
    Fl_Double_Window::resize(x, y, w, h);
    _xGl = Fl_Double_Window::x() + border;
    _yGl = Fl_Double_Window::y() + border;
    _wGl = Fl_Double_Window::w() - border;
    _hGl = Fl_Double_Window::h() - border;

    if (s_GladInitialized) {
        printf("x=%i y=%i w=%i h=%i\n", x, y, w, h);
        resizeGlWindow(_xGl, _yGl, _wGl, _hGl);
        glViewport(_xGl, _yGl, _wGl, _hGl);
    }
    damage(FL_DAMAGE_ALL);
    Fl_Double_Window::draw();
}

void Fr_GL3Window::resizable(Fl_Widget* w)
{
    Fl_Double_Window::resizable(w);
    
}

int Fr_GL3Window::GLFWrun()
{
    //TODO DOSENT WORK .. WHY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
    //Fl::add_timeout(1, redrawFLTKTimer_cb, pfltkWindow);       // 24fps timer
    //Fl::wait(1);
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
        if (fltktimerValue >= redrawFPS){
            fltktimerValue = 0.0;
            redrawFLTKTimer_cb(this);
        }

        // render
        // ------

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
        glad_glFlush();
    }
    return 0;
}

Fr_GL3Window::Fr_GL3Window(int w, int h, const char* l) :Fl_Double_Window(0, 0, w, h, l) {}
Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h) : Fl_Double_Window(x, y, w, h, "TestOpenGl") {}
Fr_GL3Window::Fr_GL3Window(int w, int h) : Fl_Double_Window(0, 0, w, h, "TestOpenGl") {}