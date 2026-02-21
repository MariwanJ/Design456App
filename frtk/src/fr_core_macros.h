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
#ifndef FR_COMMON_H
#define FR_COMMAN_H
#include <frtk.h>
#include <fr_core.h>

namespace FR {
    // Get Current Directory
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

// FR DEBUG BREAK, USE IT WHEN YOU WANT TO BREAK WITH SOME IF CONDITION 2026/02/09
#if defined(_WIN32)
#define FR_DEBUG_BREAK __debugbreak()
#elif defined(__linux__) || defined(__APPLE__)
#include <signal.h>
#define FR_DEBUG_BREAK raise(SIGTRAP)
#else
#define FR_DEBUG_BREAK ((void)0)
#endif

// Assertions
#ifdef FRTK_ENABLE_ASSERTS
#define FRTK_CORE_APP_ASSERT(x, ...) do { if(!(x)) FR_DEBUG_BREAK; } while(0)
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
#if defined(FR_BUILD_STATIC)
#define FRTK_API

// Windows
#elif defined(_WIN32) || defined(__CYGWIN__)
#if defined(FR_BUILD_DLL)
#define FRTK_API __declspec(dllexport)
#else
#define FRTK_API __declspec(dllimport)
#endif

// GCC / Clang (Linux, macOS, etc.)
#elif defined(__GNUC__) || defined(__clang__)
#define FRTK_API __attribute__((visibility("default")))

// Fallback
#else
#define FRTK_API
#endif

#define setBIT(x) (1 << x)
#define clearBIT(x) (0 << x)
#define APPLY_OPACITY(c, alpha) ((c.a *= (alpha), c.a = (c.a < 0.0f ? 0.0f : (c.a > 1.0f ? 1.0f : c.a)), c.r), (c.g), (c.b), (c.a))

    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException() : std::logic_error{ "not implemented." } {}
    };

    inline bool GLLogCall()
    {
        bool ok = true;
        GLenum error;

        while ((error = glGetError()) != GL_NO_ERROR)
        {
            std::cout << "[OpenGL Error] {" << error << "}\n";
            ok = false;
        }

        std::cout << std::flush;
        return ok;
    }
}

#endif
