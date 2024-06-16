
#include <base_application.h>
#include <base_window.h>

int main(int argc, char* argv) {
  // Dynamically allocate the window to ensure it is properly managed
  auto w = std::make_unique<BaseWindow>();
  w->Init(400, 400, "Hello World");

  BaseApplication app;
  app.RegisterWindow(w.release());
  app.Run();
  return 0;
}