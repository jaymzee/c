#include <windows.h>
#include <stdio.h>

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
    if(ret)
    {
        printf("Console Buffer Width: %d\n", csbi.dwSize.X);
        printf("Console Buffer Height: %d\n", csbi.dwSize.Y);
    }

    return 0;
}
