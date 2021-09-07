#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

void getCursor(int *x, int *y)
{
   printf("\033[6n");  /* This escape sequence !writes! the current
                          coordinates to the terminal.
                          We then have to read it from there, see [4,5].
                          Needs <termios.h>,<unistd.h> and some others */
   scanf("\033[%d;%dR", x, y);
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
