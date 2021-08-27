#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// query windows console size. similar to
// $ stty size
//
// works in windows console and windows terminal
// but not in mintty so check if stty is avail first
// and call system

struct screen {
    int rows;
    int cols;
};

void get_console_size(struct screen *scr) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    scr->cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    scr->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int stty_size(struct screen *scr)
{
    FILE *fp;
    char buf[1024];

    /* Open the command for reading. */
    fp = popen("stty size", "r");
    if (fp == NULL) {
        // fp is not null on popen errors on windows
        // instead the error is sent to stderr during the
        // fgets call below which is really weird.

        // indicate failure
        return 0;
    }
    /* Read the output. */
    fgets(buf, sizeof(buf), fp);
    pclose(fp);

    // this little check because of windows mentioned above
    int len = strlen(buf);
    if (len < 4 || len > 10) {
        return 0;
    }
    sscanf(buf, "%d %d", &scr->rows, &scr->cols);

    // indicate success
    return 1;
}

int main(int argc, char *argv[]) {
    struct screen scr;

    get_console_size(&scr); // this might produce garbage not windows console
    stty_size(&scr);        // this will have no effect in windows console
    printf("%d %d\n", scr.rows, scr.cols);

    return 0;
}
