
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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <glm/gtc/type_ptr.hpp>
#include<glad/glad.h>
#include <fr_core.h>
#include <fr_shader_program.h>

ShaderProgram::ShaderProgram(const std::string& prefix) :
    program_((glCreateProgram())) {
    CompileShader(GL_VERTEX_SHADER, prefix + "_vs.glsl"); 
    CompileShader(GL_FRAGMENT_SHADER, prefix + "_fs.glsl");
    LinkShader();
}

ShaderProgram::~ShaderProgram() {
    glCheckFunc(glDeleteProgram(program_));
}

unsigned int ShaderProgram::GetHandle() {
    return program_;
}

std::string ShaderProgram::ReadFile(const std::string& path) {
    std::ifstream input(path);
    if (!input.is_open())
        throw std::runtime_error("Unable to open file: " + path);
    std::string output;
    while (!input.eof()) {
        char line[1024];
        input.getline(line, 1024);
        output = output + line + "\n";
    }
    return output;
}

void ShaderProgram::Enable() {
    glCheckFunc( glUseProgram(program_));
}

void ShaderProgram::Disable() {
    glCheckFunc(glUseProgram(0));
}

void ShaderProgram::SetUniformInteger(const std::string& name, int value) {
    GLuint location = glGetUniformLocation(program_, name.c_str() );
    glCheckFunc(glUniform1i(location, value));
}

void ShaderProgram::SetUniformFloat(const std::string& name, float value) {
    GLuint location = glGetUniformLocation(program_, name.c_str());
    glCheckFunc(glUniform1f(location, value));
}

void ShaderProgram::SetUniformVec3(const std::string& name,
        const glm::vec3& value) {
    GLuint location = glGetUniformLocation(program_, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniformVec4(const std::string& name,
        const glm::vec4& value) {
    GLuint location = glGetUniformLocation(program_, name.c_str());
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniformMat4(const std::string& name,
        const glm::mat4& value) {
    GLuint location = glGetUniformLocation(program_, name.c_str());
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::SetAttribLocation(const char *name, unsigned int location) {
    glCheckFunc(glBindAttribLocation(program_, location, name));
}

void ShaderProgram::CompileShader(int shader_type, const std::string& path) {
    auto shader_str = ReadFile(path);
    auto shader_cstr = shader_str.c_str();
    auto shader = glCreateShader(shader_type);
    glCheckFunc( glShaderSource(shader, 1, &shader_cstr, NULL));
    glCheckFunc(glCompileShader(shader));
    GLint success = 0;
    glCheckFunc(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLint length = 0;
        glCheckFunc(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
        
        char *log=new char(length);
        glCheckFunc(glGetShaderInfoLog(shader, length, &length, log));
        glCheckFunc(glDeleteShader(shader));
        throw std::runtime_error(log);
        delete log;
    }
    glCheckFunc(glAttachShader(program_, shader));
}

void ShaderProgram::LinkShader() {
    glCheckFunc( glLinkProgram(program_));
    GLint program_linked;
    glGetProgramiv(program_, GL_LINK_STATUS, &program_linked);
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program_, 1024, &log_length, message);
        // Write the error to a log
    }

    // TODO verify status
}

