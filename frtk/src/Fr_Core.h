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

#ifndef FR_CORE_H
#define FR_CORE_H

#include <frtk.h>
#pragma once

// -------------------- OpenGL / GLAD / GLFW --------------------
#if defined(__APPLE__)
#error FRTK NOT IMPLEMENTED FOR APPLE
#else
#define GLAD_STATIC 1
#include <glad/glad.h>          // Modern OpenGL loader
#include <GLFW/glfw3.h>         // GLFW context and window
#include <GLFW/glfw3native.h>   // Native access (X11 on Linux)
#undef None                      // Fix X11 macro conflict
#endif

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// -------------------- Standard Libraries --------------------
#include <string>
#include <cstring>
#include <cerrno>
#include <limits.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <direct.h>  // _getcwd
#else
#include <unistd.h>  // getcwd
#endif

// -------------------- Get Current Directory --------------------
#if defined(_WIN32) || defined(_WIN64)
#define GET_CURRENT_DIRECTORY() []() { \
        char buffer[MAX_PATH]; \
        _getcwd(buffer, MAX_PATH); \
        return std::string(buffer); \
    }()
#else
#define GET_CURRENT_DIRECTORY() []() { \
        char buffer[PATH_MAX]; \
        if(getcwd(buffer, sizeof(buffer))) { \
            return std::string(buffer); \
        } else { \
            return std::string("Error: ") + strerror(errno); \
        } \
    }()
#endif


// -------------------- Logging / Instrumentation --------------------
#include <fr_constants.h>
#include <Fr_Log.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "../instrumentation/Instrumentor.h"

// -------------------- ImGui / GLM / Widgets --------------------
#include <glm/glm.hpp>
#include <imgui.h>
#include <ImGuizmo.h>
#include "widgets/imgui_toolbars.h"

// ImGui Fonts
#include "imguiFont/IconsFontaudio.h"
#include "imguiFont/IconsFontAwesome6.h"
#include "imguiFont/IconsFontAwesome6Brands.h"
#include "imguiFont/IconsForkAwesome.h"
#include "imguiFont/IconsKenney.h"
#include "imguiFont/IconsMaterialDesign.h"

// -------------------- STB Image --------------------
#include "../vendor/stb_image/src/stb_image.h"

// -------------------- OpenMesh --------------------
// Must be included after GLAD/OpenGL
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

typedef OpenMesh::PolyMesh_ArrayKernelT<> MyMesh;

// -------------------- FRTK Core --------------------
namespace FR {
	// VBO buffers
	constexpr int NUM_OF_VBO_BUFFERS = 7;
	constexpr int POSITION_VERTEX_VB = 0;
	constexpr int TEXCOORD_VB = 1;
	constexpr int NORMAL_VB = 2;
	constexpr int INDICES_VB = 3;
	constexpr int POSITION_POINTS_VB = 4;
	constexpr int COLOR_POINTS_VB = 5;
	constexpr int TEXT_VB = 6;


	//used to find path for diff resources
	extern std::string EXE_CURRENT_DIR;
	extern std::string fontPath;
	extern std::string DEFAULT_FONT;

	// Debug break
#if defined(_WIN32)
#define DEBUG_BREAK __debugbreak()
#elif defined(__linux__) || defined(__APPLE__)
#include <signal.h>
#define DEBUG_BREAK raise(SIGTRAP)
#else
#define DEBUG_BREAK ((void)0)
#endif

// Assertions
#ifdef FRTK_ENABLE_ASSERTS
#define FRTK_CORE_APP_ASSERT(x, ...) do { if(!(x)) DEBUG_BREAK; } while(0)
#else
#define FRTK_CORE_APP_ASSERT(x, ...)
#endif

// OpenGL error helpers
#define GLResetError() while(glGetError() != GL_NO_ERROR)
#ifdef _DEBUG
#define glCheckFunc(x) do { GLResetError(); x; FRTK_CORE_APP_ASSERT(GLLogCall()); } while(0)
#else
#define glCheckFunc(x) x
#endif

// Cross-platform API export macros
#if defined(_WIN32)
#ifdef FR_BUILD_STATIC
#define FRTK_API
#else
#ifdef FR_BUILD_DLL
#define FRTK_API __declspec(dllexport)
#else
#define FRTK_API __declspec(dllimport)
#endif
#endif
#elif defined(__linux__)
#ifdef FR_BUILD_STATIC
#define FRTK_API
#else
#ifdef FR_BUILD_DLL
#define FRTK_API __attribute__((visibility("default")))
#else
#define FRTK_API
#endif
#endif
#else
#error FRTK NOT IMPLEMENTED FOR THIS PLATFORM
#endif

#define setBIT(x) (1 << x)
#define clearBIT(x) (0 << x)

	std::string separateFN(std::string& st);

	class Fr_Window;
		//PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT,
	#define PERSPECTIVE   0
	#define ORTHOGRAPHIC  1
	#define TOP           2
	#define BOTTOM        3
	#define FRONT         4
	#define BACK          5
	#define RIGHT         6
	#define LEFT          7

 // Function to convert string to int
	uint8_t getCameraIndex(const char* name);
	const char* getCameraName(uint8_t v);

	//Mouse Ray
	typedef struct {
		glm::vec3 position;
		glm::vec3 direction;
	}ray_t;

	typedef struct {
		int x;
		int y;
		int w;
		int h;
	}screenDim_t;

	struct userData_S {
		glm::vec3 camm_position;
		glm::vec3 direction_;
		glm::vec3 up_;
		float fovy_;
		float znear_;
		float zfar_;
		float aspectRatio_;
		float orthoSize_;
		//        projectionm_Matrix(glm::ortho(-600, 600, -600, 600, -1, 1)),
		uint8_t camType_;
	};
	typedef userData_S userData_;

	static unsigned char GLLogCall() {
		while (GLenum error = glGetError()) {
			std::cout << "[OpenGL Error] {" << error << "}\n";
			std::flush(std::cout);
			return 0;
		}
		return 1;
	}
	//Used for 2D Drawing, maybe 3D also? TODO:FIXME
	enum twodType_t {
		FR_NOT_DEFINED = -1,
		FR_POINT = 0,
		FR_LINES,
		FR_OPEN_LOOP,
		FR_CLOSED_LOOP, //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
		FR_CIRCLE,
		FR_CURVE,
		FR_ARC,
		FR_BSPLINE,
	};

	enum FR_EVENTS {
		FR_NO_EVENT = 0,     //DONT CARE EVENT

		FR_LEFT_PUSH,
		FR_RIGHT_PUSH,
		FR_MIDDLE_PUSH,

		FR_LEFT_RELEASE,
		FR_RIGHT_RELEASE,
		FR_MIDDLE_RELEASE,

		FR_LEFT_DRAG_PUSH,
		FR_LEFT_DRAG_RELEASE,

		FR_RIGHT_DRAG_PUSH,
		FR_RIGHT_DRAG_RELEASE,

		FR_MIDDLE_DRAG_PUSH,
		FR_MIDDLE_DRAG_RELEASE,

		FR_MOUSE_MOVE,

		FR_ENTER,
		FR_FOCUS,
		FR_KEYBOARD,
		FR_CLOSE,
		FR_DEACIVATE,
		FR_ACTIVE,
		FR_HIDE,
		FR_SHOW,

		FR_WINDOW_RESIZE,
		FR_WINDOW_MINIMIZE,
	};

	//Define all kind of widgets here, YOU MUST DO THIS!!
	typedef enum class NODETYPE {
		FR_NODE = 0,
		FR_GROUP = 1,
		FR_TRANSFORM = 2,
		FR_MANIPULATOR = 3,
		FR_PRIMATIVESHADER = 4,
		FR_LIGHT = 5,
		FR_CAMERA = 6,
		FR_MODEL_NODE = 7,
		FR_SCENE = 8,
		FR_SHAPE = 9,
		FR_MESH = 10,
		FR_GRID = 11,
		FR_AXIS3D,
		//FR WIDGETS
		FR_WIDGET = 12,
		FR_WGROUP = 13,
		FR_WINDOW = 14,
		FR_LINE_WIDGET = 15,
		FR_FACE_WIDGET = 16,
	}NODETYPE;


} //FR
#endif