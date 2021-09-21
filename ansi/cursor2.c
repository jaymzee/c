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

int main()
{
    struct termios saved, temp;
    const char *dev;
    int fd;
    int x=0, y=0;

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

    getCursor(&x, &y);

    // restore terminal settings
    tcsetattr(fd, TCSANOW, &saved);
    close(fd);

    // print results
    printf("cursor: %d %d\n", x, y);

    exit(0);
}
