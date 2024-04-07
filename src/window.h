#pragma once

#include "kijin_export.h"

#include <array>
#include <string>

struct pimpl;
struct GLFWmonitor;
struct GLFWwindow;

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
