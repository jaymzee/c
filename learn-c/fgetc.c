#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if (argc != 2) {
        printf("Usage: hello <filename>\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        perror(argv[1]);
        return 1;
    }

    while ((c = fgetc(fp)) != EOF)
        putchar(c);

    return 0;
}
