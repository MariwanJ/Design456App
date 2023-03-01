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

#ifndef FR_CORE_H
#define FR_CORE_H

#include <FR.h>
#include <frtk.h>

#include<Fr_Log.h>

#if defined(__APPLE__)
#  include <OpenGL/gl3.h> // defines OpenGL 3.0+ functions
#else
#if defined(_WIN32)
#define GLAD_STATIC 1
#include<glad/glad.h>
#endif



#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Fr_Log.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <../instrumentation/Instrumentor.h>
//imGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <widgets/imgui_toolbars.h>

//imGUI fonts 

#include<imguiFont/IconsFontaudio.h>
#include<imguiFont/IconsFontAwesome6.h>
#include<imguiFont/IconsFontAwesome6Brands.h>
#include<imguiFont/IconsForkAwesome.h>
#include<imguiFont/IconsKenney.h>
#include<imguiFont/IconsMaterialDesign.h>

#include<glm/glm.hpp>
//PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT, 
enum class CameraList {
    PERSPECTIVE = 0, //This is not fixed and can be moved , others are not.
    ORTHOGRAPHIC,
    TOP,
    BOTTOM,
    RIGHT,
    LEFT,
    FRONT,
    BACK,
};
typedef struct userData_ {
    glm::vec3 camPosition_;
    glm::vec3 direction_;
    glm::vec3 up_;
    float fovy_;
    float znear_;
    float zfar_;
    float aspectRatio_;
    //        projectionMatrix_(glm::ortho(-600, 600, -600, 600, -1, 1)),
    CameraList camType_;
};











#ifdef _WIN32
#define DEBUG_BREAK __debugbreak()
#elif defined(__APPLE__)
DEBUG_BRAK  raise(SIGTRAP)   //Not sure if it works TODO : CHECKME
#elif define(__linux__)
DEBUG_BRAK  raise(SIGTRAP)   //ALL POSIX OS
#endif

/* Use this only for GLAD - Not used with GLFW calls
*  You should also have a valid GLAD initialization
*/
#ifdef FRTK_ENABLE_ASSERTS
#define FRTK_CORE_APP_ASSERT(x, ...)  if(!(x)) DEBUG_BREAK;
#else
#define FRTK_CORE_APP_ASSERT(x, ...)
#endif
static unsigned char GLLogCall() {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] {" << error << "}\n";
        std::flush(std::cout);
        return 0;
    }
    return 1;
}
#define GLResetError {while(glGetError() != GL_NO_ERROR);}
#ifdef _DEBUG
#define glCheckFunc(x) GLResetError;x; FRTK_CORE_APP_ASSERT(GLLogCall());
#else
#define glCheckFunc(x)  x;
#endif

//Create DLL/SO or link statically ?

#ifdef FRTK_PLATFORM_WINDOWS  //PLATFORM CHECK
#include <Windows.h>
#ifdef FR_BUILD_STATIC
#define FRTK_API 			//NOTHING
#else
#ifdef FR_BUILD_DLL
#define FRTK_API __declspec(dllexport)
#else
#define FRTK_API __declspec(dllimport)
#endif
#endif
#else
#error FRTK NOT IMPLEMENTED
#endif  //PLATFORM CHECK

#endif

#define setBIT(x) (1 << x)
#define clearBIT(x) (0 << x)

#endif