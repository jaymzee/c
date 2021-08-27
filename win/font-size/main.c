#include <windows.h>
#include <stdio.h>

/*
typedef struct _CONSOLE_FONT_INFO {
  DWORD nFont;
  COORD dwFontSize;
} CONSOLE_FONT_INFO, *PCONSOLE_FONT_INFO;

BOOL WINAPI GetCurrentConsoleFont(
   HANDLE             hConsoleOutput,
   BOOL               bMaximumWindow,
   PCONSOLE_FONT_INFO lpConsoleCurrentFont
);

*/

/* Get the window width */
int getww(void)
{
    CONSOLE_FONT_INFO info;
    GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
    return info.dwFontSize.X;
}

/* Get the window height */
int getwh(void)
{
    CONSOLE_FONT_INFO info;
    GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
    return info.dwFontSize.Y;
}

int main()
{
    int w, h;

    w = getww();
    h = getwh();

    printf("%d x %d\n", w, h);
}
