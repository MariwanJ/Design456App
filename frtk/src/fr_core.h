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
//  Author : Mariwan Jalal   mariwan.jalal@gmail.com
//

#ifndef FR_CORE_H
#define FR_CORE_H

#include <frtk.h>

//  OpenGL / GLAD / GLFW
#if defined(__APPLE__)
#error FRTK NOT IMPLEMENTED FOR APPLE
#else
#define GLAD_STATIC 1
#include <glad/glad.h>          // Modern OpenGL loader
#include <GLFW/glfw3.h>         // GLFW context and window
#include <GLFW/glfw3native.h>   // Native access (X11 on Linux)
#include <fr_core_macros.h>

//NanoVG
#include <nanovg.h>

#undef None                      // Fix X11 macro conflict
#endif

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Standard Libraries
#include <string>
#include <cstring>
#include <cerrno>
#include <limits.h>


//beep 
#if defined(_WIN32)
#include <windows.h>
#define FRTK_BEEP MessageBeep(MB_ICONASTERISK)

#elif defined(__APPLE__)

#include <AudioToolbox/AudioToolbox.h>
#define FRTK_BEEP AudioServicesPlayAlertSound(kSystemSoundID_UserPreferredAlert)

#else

#include <cstdio>
#define FRTK_BEEP \
        do { std::fputc('\a', stdout); std::fflush(stdout); } while (0)
#endif



#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <direct.h>  // _getcwd
#else
#include <unistd.h>  // getcwd
#endif

// Logging / Instrumentation
#include <fr_constants.h>
#include <fr_log.h>

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#define SPDLOG_FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "../instrumentation/Instrumentor.h"

// ImGui / GLM / Widgets
#include <glm/glm.hpp>
#include <imgui.h>
#include <ImGuizmo.h>
#include <fr_openmesh.h>

// ImGui Fonts
#include <imguiFont/shapes_ttf.h>

// STB Image
#include <stb_image.h>

// OpenMesh
// Must be included after GLAD/OpenGL
using MyMesh = FR::FrOpenMesh;

// FRTK Core
namespace FR {
    // VBO buffers
   // VBO buffers
    constexpr int NUM_OF_VBO_BUFFERS = 5;
    constexpr int POSITION_VERTEX_VB = 0;
    constexpr int POSITION_NORMAL_VB = 1;
    constexpr int POSITION_TEXCOORD_VB = 2;
    constexpr int INDICES_VB = 3;
    constexpr int POSITION_POINTS_VB = 4;

    //Shader position - this is NOT VBO position
    constexpr int SHADER_POS_VERTEX_VB = 0;
    constexpr int SHADER_POS_NORMAL_VB = 1;
    constexpr int SHADER_POS_TEXTURE_VB = 2;
    constexpr int SHADER_POS_POINTS_VB = 0; //HAS DIFF SHADER

    //used to find path for diff resources
    extern std::string EXE_CURRENT_DIR;
    extern std::string fontPath;
    extern std::string iconPath;

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
        float w;
        float h;
    }dimSize_float_t;

    typedef struct {
        float x;
        float y;
    }dimPos_float_t;

    typedef struct {
        int w;
        int h;
    }dimSize_int_t;

    typedef struct {
        int x;
        int y;
    }dimPos_int_t;

    typedef struct {
        dimPos_float_t pos;
        dimSize_float_t size;
    } Dim_float_t;

    typedef struct {
        dimPos_int_t pos;
        dimSize_int_t size;
    } screenDim_t;

    typedef struct {
        glm::vec3 cam_pos_;
        glm::vec3 direction_;
        glm::vec3 up_;
        float fovy_;
        float znear_;
        float zfar_;
        float aspectRatio_;
        float orthoSize_;
        uint8_t camType_;
    }userData_t;

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

    //Holds Unicode char for later processing
    typedef struct {
        uint32_t codepoint;
    } CharEvent_t;

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
    /*
    Events explanations:
    1- FR_FOCUS :
    2- FR_XXX_PUSH ->    Mouse button xxx pushed
    3- FR_XXX_RELEASE    Mouse button xxx released
    4- FR_XXX_DRAG_PUSH  Mouse button xxx is pushed continuously and MOUSE-MOVE also happen
    5- FR_MOUSE_MOVE     Mouse moves
    6- FR_SCROLL         Scroll wheel rotated
    7- FR_ENTER          Enter pressed (Left - Right)
    8- FR_KEYBOAR        Keyboard pressed
    9- FR_CLOSE          User clicks the window manager X button
                         User presses Alt+F4 / Cmd+W
    10-FR_DEACTIVATE     Windows sends the event ..
       FR_ACTIVATE
    11-FR_HIDE/SHOW      Windows sends these event to childrens
    12-FR_WINDOW_RESIZE/ Windows sends these events
       FR_WINDOW_MINIMIZE
      You call window->hide()
    */
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
        FR_LEFT_DRAG_MOVE,

        FR_RIGHT_DRAG_PUSH,
        FR_RIGHT_DRAG_RELEASE,
        FR_RIGHT_DRAG_MOVE,

        FR_MIDDLE_DRAG_PUSH,
        FR_MIDDLE_DRAG_RELEASE,
        FR_MIDDLE_DRAG_MOVE,

        FR_MOUSE_MOVE,
        FR_SCROLL,

        FR_ENTER,
        FR_LEAVE,
        FR_FOCUS,
        FR_UNFOCUS,
        FR_KEYBOARD,
        FR_UNICODE,
        FR_CLOSE,
        FR_DEACIVATE,
        FR_ACTIVE,
        FR_HIDE,
        FR_SHOW,

        FR_WINDOW_RESIZE,
        FR_WINDOW_MINIMIZE,
    };

    //Define all kind of MESH-widgets here, YOU MUST DO THIS!!
    typedef enum NODETYPE {
        FR_NODE = 0,
        FR_GROUP = 100,
        FR_LIGHT = 101,
        FR_AXIS3D = 102,
        FR_WIDGET = 103,
        FR_WINDOW = 104,
        FR_GRID = 105,
        //   FR_TRANSFORM            =    ,
        //   FR_CAMERA               =    ,

             //point-based widgets 2D
        FR_POINT_WIDGET = 10000,

        //line/edge-based widgets 2D
        FR_LINE_WIDGET = 20000,

        //Face based widgets (polygon) 2D
        FR_FACE_WIDGET = 30000,

        //3D based widgets
        FR_SHAPE = 40000,
    }NODETYPE;

    //Update this as needed - FRTK GUI ENUM
    typedef enum WIDGTYPE {
        FRTK_WIDGET,
        FRTK_GROUP,
        FRTK_WINDOW,
        FRTK_BOX,

        FRTK_NORMAL_BUTTON,
        FRTK_RETURN_BUTTON,
        FRTK_REPEAT_BUTTON,
        FRTK_LIGHT_BUTTON,
        FRTK_SWITCH_BUTTON,
        FRTK_TOGGLE_BUTTON,
        FRTK_CHECK_BUTTON,
        FRTK_ROUND_BUTTON,
        FRTK_TOGGLE_ROUND_BUTTON,
        FRTK_TOGGLE_LIGHT_BUTTON,

        FRTK_LABEL,
        //input widgets
        FRTK_BASE_INPUT,
        FRTK_INPUT,
        FRTK_INT_INPUT,
        FRTK_FLOAT_INPUT,
        FRTK_DOUBLE_INPUT,
        FRTK_MULTILINE_INPUT,
        FRTK_SECRET_INPUT,
        FRTK_INPUT_READONLY,
        FRTK_NORMAL_OUTPUT,
        FRTK_MULTILINE_OUTPUT,
        FRTK_INPUT_WRAP,
        FRTK_MULTILINE_INPUT_WRAP,
        FRTK_MULTILINE_OUTPUT_WRAP,
        FRTK_NORMAL_OUTPUT_READONLY,
        FRTK_MULTILINE_OUTPUT_READONLY,
        FRTK_MULTILINE_OUTPUT_WRAP_READONLY,

        FRTK_VSCROLL,
        FRTK_HSCROLL,
        FRTK_TABWDG,
        FRTK_TABS,
        FRTK_IMAGE,
        FRTK_TOOLBAR,           //No separate FRTK windows will be created
        FRTK_TOOLBARWIN,        //Separate FRTK Window is created
        FRTK_TOOLBARWIN_TOOGLE, //Separate FRTK Window is created - but buttons are TOGGLE buttons
        FRTK_TOOLBAR_BUTTON,
    } WIDGTYPE;

    typedef enum SelectionMode
    {
        MESH = 0,
        FACE,
        EDGE,
        VERTEX
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

        bool L_Down, R_Down, M_Down;
        bool L_Pressed, L_Released, L_Drag;
        bool R_Pressed, R_Released, R_Drag;
        bool M_Pressed, M_Released, M_Drag;

        bool L_WasDragging, R_WasDragging, M_WasDragging;
        bool L_DragReleased, R_DragReleased, M_DragReleased;

        bool mouseMoved;
        bool mouseEntered; //Entered Windows area or not
        int lastMAction;
        int lastMod;
        glm::vec3 worldPos;      // world mouse position

        int button;              // which button triggered last action
        int isDClick;            // double click flag
    }mouse_t;

    typedef struct {
        int key;
        int scancode;
        int action;
        int mods;
    }KeyEvent_t;

    typedef struct {
        bool keyDown[GLFW_KEY_LAST + 1];
        std::vector<KeyEvent_t> events;
        int lastKey;
        int lastKAction;

        int scancode;
        int lastMod;
        bool shiftDown;
        bool ctrlDown;
        bool altDown;
        bool superDown;
    }Keybaord_t;

    /*Structure changed to prevent bugs
    (Keyboards events are separated from mouse
     as some of the variable names are the same)*/
    typedef struct {
        mouse_t mouse;
        Keybaord_t keyB;
    } Fr_InputEvent_t;

    //used to keep pointer to image-icon, and it's size
    typedef struct {
        std::shared_ptr<uint8_t> image;
        Dim_float_t dim;
        float opacity;
    } iconImageSize_t;

    extern float mouseClickCircleRadious;


} //FR
#endif