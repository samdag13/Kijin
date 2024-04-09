#pragma once
#include <GL/glew.h>

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

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
#define LOG(x)
#else
#define LOG(x)
#endif

void AdjustIncrement(float &increment, float component);
void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer
{

private:
public:
    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};