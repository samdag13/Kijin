#include "window.h"
#include <GLFW/glfw3.h>

struct pimpl
{
    GLFWwindow *handle{nullptr};
    int width;
    int height;
};

window::window() : Pimpl(new pimpl)
{
}

window::~window()
{
    delete Pimpl;
}

bool window::init(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
{

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Pimpl->width = width;
    Pimpl->height = height;
    Pimpl->handle = glfwCreateWindow(Pimpl->width, Pimpl->height, title, monitor, share);

    if (!Pimpl->handle)
        return false;

    glfwMakeContextCurrent(Pimpl->handle);
    glfwSetFramebufferSizeCallback(Pimpl->handle, fb_resize_callback);
    glfwSwapInterval(1);

    // Verify that glew init succeeds, which makes the link between the openGL implementation of the hardware and the standard function calls.
    if (glewInit() != GLEW_OK)
    {
        return false;
    }

    return true;
}

// TODO: Load openGL functions with GLEW, include & compile glew
bool window::run()
{
    while (!glfwWindowShouldClose(Pimpl->handle))
    {
        /*Render here*/

        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(Pimpl->handle);

        // Event polling
        glfwPollEvents();
    }
    glfwTerminate();
    return false;
}

void window::fb_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
}
