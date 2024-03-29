#include "window.h"
#include <GLFW/glfw3.h>

struct pimpl
{
    GLFWwindow *handle{nullptr};
};

window::window() : Pimpl(new pimpl)
{
}

window::~window()
{
    delete Pimpl;
}
