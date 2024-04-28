#pragma once

#include <GL/glew.h>
#include <iostream>

#ifdef OGL_DEBUG
#define LOG(x) std::cout << x << std::endl
#define ASSERT(y) \
    if (!(y))     \
        __debugbreak();
#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#elif defined(OGL_RELEASE)
#define GLCall(x) x
#define ASSERT
#define LOG(x)
#else
#define LOG(x)
#endif

inline void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

inline bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl Error] (" << error << ") " << function
                  << " " << file << ": " << line << std::endl;
        return false;
    }

    return true;
}