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


#include<Application.h>

int main(int argc, char** argv)
{
    Application* Design456App = new Application();
    Design456App->show();
    Design456App->GLFWrun();

    //return FakeMain(argc, argv);
//}
//#include <FL/Fl.H>
//#include <FL/Fl_Window.H>
//#include <FL/Fl_Button.H>
//
//#include <GLFW/glfw3.h>
//#include <glad/glad.h>
//
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>
//
//#include <windows.h>
//#include <iostream>
//
//// A simple FLTK window with one button
//Fl_Window* create_fltk_window() {
//    Fl_Window* win = new Fl_Window(200, 100, "FLTK GUI");
//    Fl_Button* btn = new Fl_Button(50, 40, 100, 30, "Hello");
//    win->end();
//    win->show();
//    return win;
//}
//#include <FL/x.H>
//int main() {
//    // Initialize GLFW
//    if (!glfwInit()) {
//        std::cerr << "Failed to init GLFW\n";
//        return -1;
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  // keep hidden until ready
//
//    GLFWwindow* glwin = glfwCreateWindow(800, 600, "GLFW + FLTK Demo", nullptr, nullptr);
//    if (!glwin) {
//        std::cerr << "Failed to create GLFW window\n";
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(glwin);
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to init GLAD\n";
//        return -1;
//    }
//
//    HWND glfw_hwnd = glfwGetWin32Window(glwin);
//
//    // Create FLTK GUI
//    Fl_Window* fl_win = create_fltk_window();
//    HWND fltk_hwnd = (HWND)fl_xid(fl_win);
//
//    // Reparent FLTK into GLFW
//    SetParent(fltk_hwnd, glfw_hwnd);
//
//    // Position FLTK window inside GLFW area
//    SetWindowPos(fltk_hwnd, HWND_TOP, 50, 50, 200, 100, SWP_SHOWWINDOW);
//
//    // Show GLFW window after reparenting
//    ShowWindow(glfw_hwnd, SW_SHOW);
//
//    // Main loop
//    while (!glfwWindowShouldClose(glwin)) {
//        // --- Render with OpenGL ---
//        glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glfwSwapBuffers(glwin);
//        glfwPollEvents();
//
//        // --- Keep FLTK responsive ---
//        Fl::check();
//    }
//
//    glfwTerminate();
//    return 0;
//}

//
//#include <FL/Fl.H>
//#include <FL/Fl_Window.H>
//#include <FL/Fl_Button.H>
//
//#include <GLFW/glfw3.h>
//#include <glad/glad.h>
//
//#include <iostream>
//#include <thread>
//#include <atomic>
//#include <chrono>
//
//// Shared state to communicate between FLTK and GLFW
//std::atomic<bool> change_color(false);
//
//// ------------------- FLTK GUI -------------------
//void fltk_button_cb(Fl_Widget* w, void*) {
//    change_color = !change_color;
//}
//
//void run_fltk() {
//    Fl_Window* win = new Fl_Window(300, 100, "FLTK GUI");
//    Fl_Button* btn = new Fl_Button(50, 30, 200, 40, "Toggle OpenGL Color");
//    btn->callback(fltk_button_cb);
//    win->end();
//    win->show();
//    Fl::run();  // FLTK event loop
//}
//
//// ------------------- GLFW OpenGL -------------------
//void run_glfw() {
//    if (!glfwInit()) {
//        std::cerr << "Failed to init GLFW\n";
//        return;
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* glwin = glfwCreateWindow(800, 600, "GLFW OpenGL Window", nullptr, nullptr);
//    if (!glwin) {
//        std::cerr << "Failed to create GLFW window\n";
//        glfwTerminate();
//        return;
//    }
//
//    glfwMakeContextCurrent(glwin);
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to initialize GLAD\n";
//        return;
//    }
//
//    while (!glfwWindowShouldClose(glwin)) {
//        // Check shared state from FLTK
//        if (change_color)
//            glClearColor(0.8f, 0.3f, 0.3f, 1.0f); // red
//        else
//            glClearColor(0.3f, 0.3f, 0.8f, 1.0f); // blue
//
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glfwSwapBuffers(glwin);
//        glfwPollEvents();
//
//        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // reduce CPU usage
//    }
//
//    glfwTerminate();
//}
//
//// ------------------- Main -------------------
//int main() {
//    // Run FLTK in main thread (recommended)
//    std::thread fltk_thread(run_fltk);
//
//    // Run GLFW in another thread
//    std::thread glfw_thread(run_glfw);
//
//    // Wait for both
//    fltk_thread.join();
//    glfw_thread.join();
//
//    return 0;
//}

//
//
//#include <FL/Fl.H>
//#include <FL/Fl_Window.H>
//#include <FL/Fl_Button.H>
//#include <FL/Fl_Slider.H>
//
//#include <GLFW/glfw3.h>
//#include <glad/glad.h>
//
//#include <thread>
//#include <atomic>
//#include <iostream>
//#include <chrono>
//#include <cmath>
//
//// ------------------- Shared State -------------------
//struct CubeControl {
//    std::atomic<bool> rotate{ true };
//    std::atomic<float> speed{ 1.0f };
//} cubeControl;
//
//// ------------------- FLTK GUI -------------------
//void toggle_rotate_cb(Fl_Widget* w, void*) {
//    cubeControl.rotate = !cubeControl.rotate.load();
//}
//
//void speed_slider_cb(Fl_Widget* w, void*) {
//    Fl_Slider* slider = (Fl_Slider*)w;
//    cubeControl.speed = slider->value();
//}
//
//void run_fltk() {
//    Fl_Window* win = new Fl_Window(300, 150, "FLTK GUI");
//
//    Fl_Button* toggleBtn = new Fl_Button(50, 20, 200, 30, "Toggle Rotation");
//    toggleBtn->callback(toggle_rotate_cb);
//
//    Fl_Slider* speedSlider = new Fl_Slider(50, 70, 200, 30);
//    speedSlider->type(FL_HOR_NICE_SLIDER);
//    speedSlider->bounds(0.1, 5.0);
//    speedSlider->value(1.0);
//    speedSlider->callback(speed_slider_cb);
//
//    win->end();
//    win->show();
//    Fl::run();
//}
//
//// ------------------- OpenGL 4.6 Setup -------------------
//
//const char* vertexShaderSource = R"glsl(
//#version 460 core
//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;
//
//out vec3 fragColor;
//
//uniform mat4 model;
//uniform mat4 projection;
//
//void main() {
//    fragColor = aColor;
//    gl_Position = projection * model * vec4(aPos, 1.0);
//}
//)glsl";
//
//const char* fragmentShaderSource = R"glsl(
//#version 460 core
//in vec3 fragColor;
//out vec4 FragColor;
//
//void main() {
//    FragColor = vec4(fragColor, 1.0);
//}
//)glsl";
//
//// Cube vertex data: positions + colors
//float vertices[] = {
//    // positions        // colors
//    -0.5f,-0.5f,-0.5f, 1.0f,0.0f,0.0f,
//     0.5f,-0.5f,-0.5f, 0.0f,1.0f,0.0f,
//     0.5f, 0.5f,-0.5f, 0.0f,0.0f,1.0f,
//    -0.5f, 0.5f,-0.5f, 1.0f,1.0f,0.0f,
//    -0.5f,-0.5f, 0.5f, 1.0f,0.0f,1.0f,
//     0.5f,-0.5f, 0.5f, 0.0f,1.0f,1.0f,
//     0.5f, 0.5f, 0.5f, 1.0f,1.0f,1.0f,
//    -0.5f, 0.5f, 0.5f, 0.0f,0.0f,0.0f,
//};
//
//unsigned int indices[] = {
//    0,1,2, 2,3,0, // back
//    4,5,6, 6,7,4, // front
//    4,5,1, 1,0,4, // bottom
//    7,6,2, 2,3,7, // top
//    4,0,3, 3,7,4, // left
//    5,1,2, 2,6,5  // right
//};
//
//// ------------------- GLFW OpenGL -------------------
//void run_glfw() {
//    if (!glfwInit()) {
//        std::cerr << "Failed to init GLFW\n";
//        return;
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(600, 600, "Modern OpenGL Cube", nullptr, nullptr);
//    if (!window) {
//        std::cerr << "Failed to create GLFW window\n";
//        glfwTerminate();
//        return;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to init GLAD\n";
//        return;
//    }
//
//    glEnable(GL_DEPTH_TEST);
//
//    // -------- Create VAO/VBO/EBO --------
//    unsigned int VAO, VBO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // -------- Compile shaders --------
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    unsigned int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // Projection matrix
//    float aspect = 1.0f;
//    float projection[16] = {
//        1 / aspect,0,0,0,
//        0,1,0,0,
//        0,0,-(100 + 0.1f) / (100 - 0.1f), -1,
//        0,0,-(2 * 100 * 0.1f) / (100 - 0.1f),0
//    };
//
//    float angle = 0.0f;
//
//    while (!glfwWindowShouldClose(window)) {
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);
//
//        if (cubeControl.rotate) angle += 0.5f * cubeControl.speed.load();
//
//        // Simple rotation matrix (around Y axis)
//        float rad = angle * 3.14159f / 180.0f;
//        float model[16] = {
//            cos(rad),0,sin(rad),0,
//            0,1,0,0,
//            -sin(rad),0,cos(rad),0,
//            0,0,0,1
//        };
//
//        int modelLoc = glGetUniformLocation(shaderProgram, "model");
//        int projLoc = glGetUniformLocation(shaderProgram, "projection");
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
//        glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);
//
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    glDeleteProgram(shaderProgram);
//
//    glfwTerminate();
//}
//
//// ------------------- Main -------------------
//int main() {
//    std::thread guiThread(run_fltk);
//    std::thread glThread(run_glfw);
//
//    guiThread.join();
//    glThread.join();
//
//    return 0;
//}
