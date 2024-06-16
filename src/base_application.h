#pragma once

#include <kijin.h>
#include <base_window.h>
#include <memory>
#include <vector>

class KIJIN_API BaseApplication {
public:
    BaseApplication();
    ~BaseApplication();
    BaseApplication(const BaseApplication&) = delete; // Delete copy constructor
    BaseApplication& operator=(const BaseApplication&) = delete; // Delete copy assignment operator
    BaseApplication(BaseApplication&&) = default; // Default move constructor
    BaseApplication& operator=(BaseApplication&&) = default;

    void Run();
    //Registration
    void RegisterWindow(BaseWindow* w);
    void UnregisterWindow(BaseWindow* w);

private:
    std::vector<std::unique_ptr<BaseWindow>> Windows;
    bool ShouldClose();
};