#include "base_application.h"

#include <algorithm>
#include <iostream>

BaseApplication::BaseApplication()
{
}

BaseApplication::~BaseApplication()
{
}

void BaseApplication::Run()
{
    while (!ShouldClose()) {
        std::vector<BaseWindow*> to_destroy;
        for (auto&& w : Windows) {
            w->Draw();
            w->PollEvents();
            if (w->ShouldClose())
                to_destroy.emplace_back(w.get());

        }
        for (auto&& w : to_destroy) {
            w->Close();
            UnregisterWindow(w);
        }
    }
    return;
}

void BaseApplication::RegisterWindow(BaseWindow* w)
{
    auto it = std::find_if(Windows.begin(), Windows.end(), [&w](const auto& entry) { return entry.get() == w; });
    if (it != Windows.end()) {
        std::cout << "Window already registered: " << w << std::endl;
        return;  // Window is already registered, do nothing
    }

    std::unique_ptr<BaseWindow> window_ptr(w);
    Windows.emplace_back(std::move(window_ptr));
    std::cout << "Window registered: " << w << std::endl;
}

void BaseApplication::UnregisterWindow(BaseWindow* w)
{
    auto it = std::find_if(Windows.begin(), Windows.end(), [&w](const auto& entry) { return entry.get() == w; });
    if (it == Windows.end()) {
        std::cerr << "Error: Window not found for unregistration: " << w << std::endl;
        assert(it != Windows.end());
    }
    Windows.erase(it);
    std::cout << "Window unregistered: " << w << std::endl;
}

bool BaseApplication::ShouldClose()
{
    return Windows.empty();
}