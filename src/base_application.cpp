#include "base_application.h"

#include <algorithm>
#include <iostream>
#include <vector>

BaseApplication::BaseApplication() {}

BaseApplication::~BaseApplication() {
  // Ensure all windows are properly closed and resources are freed
  while (!Windows.empty()) {
    Windows.back()->Close();
    Windows.pop_back();
  }
}

void BaseApplication::Run() {
  while (!ShouldClose()) {
    std::vector<BaseWindow*> to_destroy;

    for (auto& w : Windows) {
      w->Draw();
      w->PollEvents();
      if (w->ShouldClose()) {
        to_destroy.push_back(w.get());
      }
    }

    for (auto* w : to_destroy) {
      UnregisterWindow(w);
    }
  }
  return;
}

void BaseApplication::RegisterWindow(BaseWindow* w) {
  auto it = std::find_if(Windows.begin(), Windows.end(),
                         [&w](const auto& entry) { return entry.get() == w; });
  if (it != Windows.end()) {
    std::cout << "Window already registered: " << w << std::endl;
    return;  // Window is already registered, do nothing
  }

  std::unique_ptr<BaseWindow> window_ptr(w);
  Windows.emplace_back(std::move(window_ptr));
  std::cout << "Window registered: " << w << std::endl;
}

void BaseApplication::UnregisterWindow(BaseWindow* w) {
  auto it = std::find_if(Windows.begin(), Windows.end(),
                         [&w](const auto& entry) { return entry.get() == w; });
  if (it == Windows.end()) {
    std::cerr << "Error: Window not found for unregistration: " << w
              << std::endl;
    assert(it != Windows.end());
  } else {
    std::cout << "Closing window: " << w << std::endl;
    w->Close();
    std::cout << "Erasing window from vector: " << w << std::endl;
    Windows.erase(it);
    std::cout << "Window unregistered: " << w << std::endl;
  }
}

bool BaseApplication::ShouldClose() { return Windows.empty(); }
