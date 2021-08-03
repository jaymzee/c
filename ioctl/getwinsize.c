#include <stdio.h>
#include <sys/ioctl.h>

int main() {
    struct winsize d;

    ioctl(0, TIOCGWINSZ, &d);
    printf("%i %i (%i x %i)\n", d.ws_row, d.ws_col, d.ws_xpixel, d.ws_ypixel);

    return 0;
}
