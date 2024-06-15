#pragma once

#include "kijin_export.h"

#include <array>
#include <string>

struct pimpl;
struct GLFWmonitor;
struct GLFWwindow;

class KIJIN_API Window
{
public:
    Window();
    virtual ~Window();

    bool Init(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
    bool Draw();

private:
    pimpl* Pimpl;

    static void FbResizeCallback(GLFWwindow* window, int width, int height);
};
