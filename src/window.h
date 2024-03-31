#pragma once

#include "kijin_export.h"
#include <GL/glew.h>

#include <array>
#include <string>

struct pimpl;
class GLFWmonitor;
class GLFWwindow;

class KIJIN_API window
{
public:
    window();
    ~window();

    bool init(int width, int height, const char *title, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);
    bool run();

private:
    pimpl *Pimpl;

    static void fb_resize_callback(GLFWwindow *window, int width, int height);
};
