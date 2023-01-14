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

//#include <FL/gl.h> // for gl_texture_reset()
#include <Fr_Log.h>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <FR.h>

#include<fr_widgets/fr_basic_shapes.h>
#include<render.h>
#include <vertexBuffer.h>
#include<indexedBuffer.h>
#include <camera.h>
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

#define setBIT(x) (1 << x)
#define clearBIT(x) (0 << x)

#endif
#endif