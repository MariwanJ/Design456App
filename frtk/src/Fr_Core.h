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

#include <FL/Fl.H>
#include <FL/fl_types.h>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>

//#include <Fr_GL3Window.h>
#include <FL/platform.H>


#include <Fr_Log.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


#include<fr_widgets/fr_basic_shapes.h>
#include <vertexBuffer.h>
#include<indexedBuffer.h>


//From Scene-graph git hub



//#include<Group.h>
//#include<Light.h>
//#include<Manipulator.h>
//#include<Mesh.h>
//#include<Camera.h>
//#include<Scene.h>
//#include<ShaderProgram.h>
//#include<ToonShaderNode.h>
//#include<Transform.h>


//From Scene-graph git hub

/*
    __linux__       Defined on Linux
    __sun           Defined on Solaris
    __FreeBSD__     Defined on FreeBSD
    __NetBSD__      Defined on NetBSD
    __OpenBSD__     Defined on OpenBSD
    __APPLE__       Defined on Mac OS X
    __hpux          Defined on HP-UX
    __osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
    __sgi           Defined on Irix
    _AIX            Defined on AIX
    _WIN32          Defined on Windows
*/
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
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] {" << error << "}\n";
        std::flush(std::cout);
        return 0;
    }
    return 1;
}
#define GLResetError {while(glGetError() != GL_NO_ERROR);}
#ifdef _DEBUG
#define glCheckFunc(x) GLResetError;x; FRTK_CORE_APP_ASSERT(GLLogCall());
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
 #include <Instrumentor.h>


#endif