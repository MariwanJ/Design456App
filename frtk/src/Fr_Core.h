/*                                                                      *
 This file is a part of the Open Source Design456App                    *
                                                                *
 Copyright (C) 2023                                                     *
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
 <http://www.gnu.org/licenses/>										*
 .																*                                                                       *
 Author :Mariwan Jalal    mariwan.jalal@gmail.com                        *
*/

#ifndef FR_CORE_H
#define FR_CORE_H

#include<Fr_Log.h>


#ifdef FRTK_ENABLE_ASSERTS
#define FRTK_APP_ASSERT(x, ...) { if(!(x)) { APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define FRTK_CORE_ASSERT(x, ...) { if(!(x)) { FR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define FRTK_ASSERT(x, ...)
#define FRTK_CORE_ASSERT(x, ...)
#endif


#ifdef FRTK_PLATFORM_WINDOWS
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
#endif




#define setBIT(x) (1 << x)
#define clearBIT(x) (0 << x)

#if defined(__APPLE__)
#  include <OpenGL/gl3.h> // defines OpenGL 3.0+ functions
#else
#if defined(_WIN32)
#define GLAD_STATIC 1
#endif
#include<../Glad/include/glad/glad.h>
#endif




#endif