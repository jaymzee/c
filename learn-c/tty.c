#include <stdio.h>
#include <unistd.h>

int main()
{
    char *tty_name = ttyname(STDIN_FILENO);

    printf("%s\n", tty_name);

    return 0;
}
