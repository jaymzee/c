#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

void getCursor(int *x, int *y)
{
   // This escape sequence queries the current coordinates from the terminal.
   printf("\033[6n");
   scanf("\033[%d;%dR", y, x);
}

int main()
{
    int x, y;

#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;

    GetConsoleMode(h, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(h, mode);
    printf("SetConsoleMode(%d)\n", mode);
#endif

    printf("querying \x1b[31mcursor\x1b[m position...\n");
    getCursor(&x, &y);
    printf("%d %d\n", y, x);
}
