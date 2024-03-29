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

    Pimpl->width = width;
    Pimpl->height = height;
    Pimpl->handle = glfwCreateWindow(Pimpl->width, Pimpl->height, title, monitor, share);

    if (!Pimpl->handle)
        return false;

    glfwMakeContextCurrent(Pimpl->handle);
    glfwSetFramebufferSizeCallback(Pimpl->handle, fb_resize_callback);

    return true;
}

// TODO: Load openGL functions with GLEW, include & compile glew
void window::run()
{
    while (!glfwWindowShouldClose(Pimpl->handle))
    {
        /*Render here*/
        // glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(Pimpl->handle);

        // Event polling
        glfwPollEvents();
    }
    glfwTerminate();
}

void window::fb_resize_callback(GLFWwindow *window, int width, int height)
{
    // glViewport(0, 0 width, height);
}
