//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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
   std::string DEFAULT_FONT;

    Fr_Application::Fr_Application(int x, int y, int w, int h, const char* l) :Fr_Window(x, y, w, h, l)
    {

    }

    Fr_Application::~Fr_Application()
    {
    }
#include <fr_icons.h>
 
    int Fr_Application::run(int argc, char** argv)
    {
        // std::string fname = "R";
        // auto n = loadImage();
         //std::shared_ptr<BYTE> IMG = n.getImage("nofile");
        EXE_CURRENT_DIR = GET_CURRENT_DIRECTORY();
        printf("Current Dir = %s\n", EXE_CURRENT_DIR.c_str());
#if defined(_WIN32) || defined(_WIN64)
        auto it = EXE_CURRENT_DIR.find("\\bin");
#else
        auto it = EXE_CURRENT_DIR.find("/bin");

#endif
        if (it == std::string::npos) {
            printf("Warning, current dir is %s\n", EXE_CURRENT_DIR.c_str());
        }
        else{
            EXE_CURRENT_DIR.erase(it);
        }
        fontPath = EXE_CURRENT_DIR + "/resources/fonts/";
        DEFAULT_FONT = fontPath + "Techfont.ttf"; 
        //DEFAULT_FONT = fontPath + "SUSEMono-Thin.ttf";

        while (true) {
            size_t it = EXE_CURRENT_DIR.find("\\"); // Find the backslash
            if (it != std::string::npos) { // Check if found
                EXE_CURRENT_DIR.replace(it, 1, "/"); // Replace with a forward slash
            }
            else {
                break; // Exit the loop if no more backslashes
            }
        }

        createGLFWwindow();
        return GLFWrun();
    }
}