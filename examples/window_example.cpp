
#include <window.h>

int main(int argc, char *argv)
{
    window w;
    w.init(400, 400, "Hello World");
    while (w.run())
        ;
    return 0;
}