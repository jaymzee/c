#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void dumpTermios(const struct termios *t) {
    printf("c_iflag: %08x\n", t->c_iflag);
    printf("c_oflag: %08x\n", t->c_oflag);
    printf("c_cflag: %08x\n", t->c_cflag);
    printf("c_lflag: %08x\n", t->c_lflag);
}

void getCursor(int *x, int *y)
{
   /* This escape sequence queries the current coordinates from the terminal.
    * The terminal responds on stdin */
   printf("\033[6n");
   scanf("\033[%d;%dR", y, x);
}

void getTerminalSize(int *lines, int *cols)
{
    // save cursor position, move cursor, query position
    // The terminal responds on stdin
    printf("\033[s\033[999;999H\033[6n");
    scanf("\033[%d;%dR", lines, cols);
    // restore cursor position
    printf("\033[u");
}

void getTerminalResolution(int *xres, int *yres)
{
    printf("\033[14t");
    scanf("\033[4;%d;%dt", xres, yres);
}

int main()
{
    struct termios saved, temp;
    const char *dev;
    int fd;
    int lines=24, cols=80;
    int xres=0, yres=0;

    // get tty
    dev = ttyname(STDIN_FILENO);
    if (!dev) {
        exit(1);
    }

    // open tty
    fd = open(dev, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        exit(1);
    }

    // save terminal settings
    if (tcgetattr(fd, &saved) < 0) {
        exit(1);
    }

    // modify terminal settings
    // - turn off ICANON so input is available immediately
    // - turn off ECHO, otherwise the response to CSI [6n will
    //   be displayed in the terminal
    // - disable receiver
    temp = saved;
    temp.c_lflag &= ~ICANON;
    temp.c_lflag &= ~ECHO;
    //temp.c_cflag &= ~CREAD;
    tcsetattr(fd, TCSANOW, &temp);

    // query cursor position
    getTerminalSize(&lines, &cols);
    getTerminalResolution(&xres, &yres);

    // restore terminal settings
    tcsetattr(fd, TCSANOW, &saved);
    close(fd);

    // print results
    printf("%d %d %d %d\n", lines, cols, xres, yres);

    exit(0);
}
