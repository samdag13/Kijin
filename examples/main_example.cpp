

int main(int argc, char *argv[])
{
    int foo = 0;
    while (true)
    {
        foo++;
        foo %= 5;
    }
    return 0;
}