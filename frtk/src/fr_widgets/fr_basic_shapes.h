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

#ifndef  FR_BASIC_SHAPES_H
#define  FR_BASIC_SHAPES_H
#include<frtk.h>


#include <../deps/linmath.h>

int draw_triangle(GLuint& vertexBuffer, GLFWwindow* pWindow);

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
unsigned int CompileShader(unsigned int type, const char*);


extern std::string vertexShaderSource  ;
extern std::string fragmentShaderSource;

const float TriangleVertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f , 0.0f, // right
    0.0f,  0.5f , 0.0f  // top
};


const float SquareVertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
const unsigned int SquareIndices[] = {  // start at 0
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

#endif