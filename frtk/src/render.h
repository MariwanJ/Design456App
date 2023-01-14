#ifndef RENDER_H
#define RENDER_H

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
        return 0;
    }
    return 1;
}
#define GLResetError {while(glGetError != GL_NO_ERROR);}
#ifdef _DEBUG
#define glCheckFunc(x) GLResetError;x; FRTK_CORE_APP_ASSERT(GLLogCall());
#endif




#endif
