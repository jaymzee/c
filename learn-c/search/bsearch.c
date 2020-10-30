#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmpstrp(const void *p1, const void *p2)
{
    return strcmp(*(char **)p1, *(char **)p2);
}

int main(const int argc, const char *argv[])
{
    const char **result;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <search str> <strings>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    qsort(&argv[2], argc - 2, sizeof(char *), cmpstrp);
    result = bsearch(&argv[1], &argv[2], argc - 2, sizeof(char *), cmpstrp);
    if (result != NULL)
        printf("%s\n", *result);
    else
        printf("%s not found\n", argv[1]);

    exit(EXIT_SUCCESS);
}
