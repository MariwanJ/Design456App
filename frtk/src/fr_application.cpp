//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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
#include <fr_application.h>
#include <glm/gtx/transform.hpp>
#include <fr_camera.h>
#include <fr_core.h>



namespace FR {

   std::string EXE_CURRENT_DIR;
   std::string fontPath;

   Fr_Application::Fr_Application(int x, int y, int w, int h, const char* l) :Fr_Window(x, y, w, h, l)
    {

    }

    Fr_Application::~Fr_Application()
    {
    }
#include <fr_icons.h>
 
    int Fr_Application::run(int argc, char** argv)
    {
 

        createGLFWwindow();
        return GLFWrun();
    }
}