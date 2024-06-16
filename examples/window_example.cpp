
#include <base_window.h>
#include <base_application.h>

int main(int argc, char* argv)
{
    BaseWindow w;
    w.Init(400, 400, "Hello World");
    BaseApplication app;
    app.RegisterWindow(&w);
    app.Run();
    return 0;
}