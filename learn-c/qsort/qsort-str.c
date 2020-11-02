#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmpch(const void *p1, const void *p2)
{
    if (*(const char *)p1 < *(const char *)p2)
        return -1;
    else
        return *(const char *)p1 > *(const char *)p2;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    qsort(argv[1], strlen(argv[1]), sizeof(char), cmpch);

    puts(argv[1]);

    return 0;
}
