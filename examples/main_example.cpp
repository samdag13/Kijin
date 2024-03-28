#include <log.h>

int main(int argc, char *argv[])
{
    int foo = 0;
    while (true)
    {
        foo++;
        foo %= 5;
        kijin::Print(std::to_string(foo));
    }
    return 0;
}