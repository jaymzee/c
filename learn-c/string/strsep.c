#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        char *str = strdup(argv[1]);
        char *token, *end = str;

        while ((token = strsep(&end, ",")) != NULL) {
            printf("'%s'\n", token);
        }

        free(str);
    }

    return 0;
}
