#include "window.h"

struct pimpl
{
    // GLFWDisplay *handle{nullptr};
};

window::window() : Pimpl(new pimpl)
{
}

window::~window()
{
    delete Pimpl;
}
