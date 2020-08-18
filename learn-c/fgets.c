#include <stdio.h>
#include <errno.h>

char buf[2000];

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc != 2) {
        printf("Usage: hello <filename>\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        perror(argv[1]);
        return 1;
    }

    while (fgets(buf, 50, fp))
        fputs(buf, stdout);

    return 0;
}
