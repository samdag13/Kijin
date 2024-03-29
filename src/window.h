#pragma once

#include "kijin_export.h"

#include <array>
#include <string>

struct pimpl;
class GLFWmonitor;
class GLFWwindow;

KIJIN_API class window
{
public:
    window();
    ~window();

    bool init(int width, int height, const char *title, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);
    void run();

private:
    pimpl *Pimpl;

    static void fb_resize_callback(GLFWwindow *window, int width, int height);
};
