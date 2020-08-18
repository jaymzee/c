#include <stdio.h>
#include <errno.h>

char buf[2000];

int main(int argc, char *argv[])
{
    FILE *fp;
    int n;

    if (argc != 2) {
        printf("Usage: hello <filename>\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        perror(argv[1]);
        return 1;
    }
    n = fread(buf, 1, 1000, fp);

    printf("%d %c %d\n", n, buf[0], (int)buf[0]);
    printf("%d\n", errno);

    return 0;
}
