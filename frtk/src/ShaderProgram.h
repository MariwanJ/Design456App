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

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include<frtk.h>
#include<fr_core.h>
#include <glm/glm.hpp>

class ShaderProgram {
public:
    /**
     * Loads, compiles and links the shader program
     * Expects a prefix (%) for the files: %_vs.glsl and %_fs.glsl
     */
    ShaderProgram(const std::string& prefix);

    /**
     * Destructor
     */
    ~ShaderProgram();

    /**
     * Enables or disables the program
     */
    void Enable();
    void Disable();

    /**
     * Sets an attribute location
     */
    void SetAttribLocation(const char *name, unsigned int location);

    /**
     * Sets an uniform variable
     */
    void SetUniformInteger(const std::string& name, int value);
    void SetUniformFloat(const std::string& name, float value);
    void SetUniformVec3(const std::string& name, const glm::vec3& value);
    void SetUniformVec4(const std::string& name, const glm::vec4& value);
    void SetUniformMat4(const std::string& name, const glm::mat4& value);

    /**
     * Obtains the shader program handle
     */
    unsigned int GetHandle();

private:
    /**
     * Reads the whole file and returns it as a string
     */
    std::string ReadFile(const std::string& path);

    /**
     * Loads and compiles a shader from a file
     */
    void CompileShader(int shader_type, const std::string& path);

    /**
     * Links the shader program
     */
    void LinkShader();

    unsigned int program_;
};

#endif

