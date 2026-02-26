#ifndef FRTK_API_H_
#define FRTK_API_H_

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



#endif // FRTK_API_H_