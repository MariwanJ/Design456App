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


#include <FL/Fl_Button.H>
#include <Fr_GL3Window.h>

/* Main application code */

int main(int argc, char** argv)
{
    Fr_GL3Window* win = new Fr_GL3Window(0, 0, 900, 600, "test");
    win->label("Click GL panel to reshape");
    
    //win->resizable(win);
    Fl_Button* b = new Fl_Button(10, 5, 50, 40, "clickme");
    win->resizable(b);
    win->show();
    //win->pfltkWindow->show();
    win->GLFWrun();
}

/*
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <../deps/linmath.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec2 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    glfwSetErrorCallback(error_callback);
    Fl_Window *win = new Fl_Window(1000, 890,"rr");
    if (!glfwInit())
        exit(EXIT_FAILURE);
    win->show();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }


    //***************************************


    HWND glfwHND = glfwGetWin32Window(window);
    HWND hwParentWindow = fl_win32_xid(win);
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
    MoveWindow(glfwHND, 0, 0, 800, 600, true); //place b at (x,y,w,h) in a
    SetParent(glfwHND, hwParentWindow);
    UpdateWindow(glfwHND);
    ShowWindow(glfwHND, SW_SHOW);
    //return 1;//everything is OK.





    //***********************************


    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, col));

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

*/