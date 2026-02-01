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

#ifndef FR_CORE_H
#define FR_CORE_H

#include <frtk.h>



// -------------------- OpenGL / GLAD / GLFW --------------------
#if defined(__APPLE__)
#error FRTK NOT IMPLEMENTED FOR APPLE
#else
#define GLAD_STATIC 1
#include <glad/glad.h>          // Modern OpenGL loader
#include <GLFW/glfw3.h>         // GLFW context and window
#include <GLFW/glfw3native.h>   // Native access (X11 on Linux)

//NanoVG 
#include <nanovg.h>

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
#define GET_CURRENT_DIRECTORY() []() -> std::string { \
        char buffer[MAX_PATH]; \
        if (_getcwd(buffer, sizeof(buffer)) != NULL) { \
            return std::string(buffer); \
        } else { \
            return std::string("Error: Unable to get current directory."); \
        } \
    }()
#else
#include <limits.h> // For PATH_MAX
#include <cstring>  // For strerror
#include <cerrno>   // For errno

#define GET_CURRENT_DIRECTORY() []() -> std::string { \
        char buffer[PATH_MAX]; \
        if (getcwd(buffer, sizeof(buffer))) { \
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
#include <fr_openmesh.h>

// ImGui Fonts
#include "imguiFont/shapes_ttf.h"

// -------------------- STB Image --------------------
#include "../vendor/stb_image/src/stb_image.h"

// -------------------- OpenMesh --------------------
// Must be included after GLAD/OpenGL
using MyMesh = FR::FrOpenMesh;

// -------------------- FRTK Core --------------------
namespace FR {
    // VBO buffers
   // VBO buffers
    constexpr int NUM_OF_VBO_BUFFERS = 5;
    constexpr int POSITION_VERTEX_VB = 0;
    constexpr int POSITION_NORMAL_VB = 1;
    constexpr int POSITION_TEXCOORD_VB = 2;
    constexpr int INDICES_VB = 3;
    constexpr int POSITION_POINTS_VB = 4;

    //constexpr int COLOR_POINTS_VB = 5;
    //constexpr int POSITION_TEXT_VB = 6;

    //Shader position - this is NOT VBO position
    constexpr int SHADER_POS_VERTEX_VB = 0;
    constexpr int SHADER_POS_NORMAL_VB = 1;
    constexpr int SHADER_POS_TEXTURE_VB = 2;
    constexpr int SHADER_POS_POINTS_VB = 0; //HAS DIFF SHADER

    //used to find path for diff resources
    extern std::string EXE_CURRENT_DIR;
    extern std::string fontPath;

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

    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException() : std::logic_error{ "not implemented." } {}
    };

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

    /**
* Holds the light information
*/
    struct LightInfo {
        glm::vec4 lightcolor;
        glm::vec4 position;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 ambient;
        glm::vec3 attenuation;
        bool is_spot;
        glm::vec3 direction;
        float cutoff;
        float exponent;
    };

    /**
     * Holds the render information
     */
    struct RenderInfo {
        int id;
        glm::mat4 modelview;
        glm::mat4 projection;
        std::vector<LightInfo> lights;
        //ShadowMapInfo shadowmap;
        //bool render_transparent;
        screenDim_t screenDim;
    };

    //Used for 2D Drawing, maybe 3D also? TODO:FIXME
    enum twodType_t {
        FR_NOT_DEFINED = -1,
        FR_POINT = 0,
        FR_LINES,
        FR_OPEN_LOOP,
        FR_CLOSED_LOOP, //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
        FR_TRIANGLE,
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
        FR_SCROLL,

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
    typedef enum NODETYPE {
        FR_NODE                 = 0,
        FR_GROUP                = 100,
        FR_LIGHT                = 101,
        FR_AXIS3D               = 102,
        FR_WIDGET               = 103,
        FR_WINDOW               = 104,
        FR_GRID                 = 105,
   //   FR_TRANSFORM            =    ,
   //   FR_CAMERA               =    ,


        //point-based widgets 2D
        FR_POINT_WIDGET         =10000,


        //line/edge-based widgets 2D
        FR_LINE_WIDGET          =20000,
        
        
        //Face based widgets (polygon) 2D
        FR_FACE_WIDGET          =30000,
        
        //3D based widgets
        FR_SHAPE                =40000,


    }NODETYPE;



    typedef enum
    {
        Mesh = 0,
        Face,
        Edge,
        Vertex
    }SelectionMode;

    //Selection mode toolbar
    extern SelectionMode  m_currentSelMode; //0 Mesh, 1 Face, 2 Edge, 3Vertex

    typedef struct {
        float MouseXYScale;
        float MouseScrollScale;
    }mouseScale_t;

    typedef struct {
        double activeX;
        double activeY;
        double prevX;
        double prevY;
        double scrollX;
        double scrollY;
    }mouse_buttons_t;

    
    typedef struct {
        // Mouse positions
        mouse_buttons_t mouse;   // activeX/Y + prevX/Y
        bool mouseEntered; //Entered Windows area or not

        glm::vec3 worldPos;      // world mouse position

        int button;              // which button triggered last action
        int isDClick;            // double click flag

        // Derived per-frame flags

        bool L_Down, R_Down, M_Down;
        bool L_Pressed, L_Released, L_Drag;
        bool R_Pressed, R_Released, R_Drag;
        bool M_Pressed, M_Released, M_Drag;
        bool mouseMoved;


        // Keyboard
        bool keyDown[GLFW_KEY_LAST + 1];
        bool prevKeyDown[GLFW_KEY_LAST + 1];
        int lastKey;
        int lastAction;
        int lastMod;
        int scancode;

        bool shiftDown ;
        bool ctrlDown ;
        bool altDown ;
        bool superDown;

    } Fr_InputEvent_t;

} //FR
#endif