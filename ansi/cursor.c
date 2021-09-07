#include <stdio.h>

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

    printf("querying cursor position...\n");
    getCursor(&x, &y);
    printf("%d %d\n", y, x);
}
