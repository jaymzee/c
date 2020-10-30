#include <search.h>
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
    size_t size = argc - 2;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <search str> <strings>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    result = lfind(&argv[1], &argv[2], &size, sizeof(char *), cmpstrp);
    if (result != NULL)
        printf("%s\n", *result);
    else
        printf("%s not found\n", argv[1]);

    exit(EXIT_SUCCESS);
}
