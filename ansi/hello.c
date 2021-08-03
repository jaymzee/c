#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;

    GetConsoleMode(h, &mode);

    if (argc > 1 && atoi(argv[1])) {
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(h, mode);
    }

    printf("Provide a cmdline arg of 1 to make sure "
           "VIRTUAL_TERMINAL_PROCESSING is enabled.\n\n");
    printf("GetConsoleMode = %lu\n\n", mode);

    printf("\e[1;31mHello\e[m\n");

    return 0;
}
