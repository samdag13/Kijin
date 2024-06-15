
#include <window.h>

int main(int argc, char *argv)
{
    Window w;
    w.Init(400, 400, "Hello World");
    while (w.Draw())
        ;
    return 0;
}