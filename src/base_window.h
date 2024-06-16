#pragma once

#include "kijin_export.h"

#include <array>
#include <string>

struct pimpl;
struct GLFWmonitor;
struct GLFWwindow;

class KIJIN_API BaseWindow
{
public:
    BaseWindow();
    virtual ~BaseWindow();

    BaseWindow(const BaseWindow&) = delete;
    BaseWindow(BaseWindow&&) noexcept = delete;
    BaseWindow& operator=(const BaseWindow&) = delete;
    BaseWindow& operator=(BaseWindow&&) noexcept = delete;

    virtual void Init(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
    virtual void Draw();
    virtual bool ShouldClose();
    virtual void Close();
    void PollEvents();

private:
    pimpl* Pimpl;

    static void FbResizeCallback(GLFWwindow* window, int width, int height);
};
