/*
 * split string - strsep implementation
 * use when you want consecutive delimiters to always count as separate fields
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(char *str, const char *del) {
    // determine how many strings str will be split into
    // using a temporary copy of str
    int count;
    char *tmp = strdup(str);
    char *end = tmp;
    for (count = 0; strsep(&end, del) != NULL; count++) {}
    free(tmp);

    // now actually split str
    char **p = malloc((count + 1) * sizeof(char *));
    end = str;
    for (int i = 0; i < count; i++) {
        p[i] = strsep(&end, del);
    }
    // NULL terminate list
    p[count] = NULL;

    return p;
}

int main(int argc, char *argv[])
{
    if (argc == 3) {
        char *str = strdup(argv[1]);
        char **strings = split(str, argv[2]);

        for (char **sptr = strings; *sptr != NULL; sptr++) {
            printf("'%s'\n", *sptr);
        }
        printf("%s\n", argv[1]);
        free(str);
    }

    return 0;
}
