#include <ncurses.h>

int main()
{
    initscr();
    curs_set(2);
    printw("setfont matrix\n");
    printw("chars 166 thru 244 of alt charset\n");
    attron(A_ALTCHARSET);
    for (int i = 166; i <= 244; i++)
        printw("%c", i);
    printw("\n");
    for (int i = 12288; i <= 12351; i++)
        printw("%c", i);
    printw("\n");
    attroff(A_ALTCHARSET);
    printw("welcome to the matrix");
    refresh();
    getch();
    endwin();

    return 0;
}
