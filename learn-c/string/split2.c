/*
 * split string - strtok implementation
 * best for splitting whitespace or anything with consecutive delimiters
 * treated as one delimiter
 */

#include <stdlib.h>
#include <string.h>

char **split(char *str, const char *del) {
    // determine how many strings str will be split into
    // using a temporary copy of str
    int count;
    char *tmp = strdup(str);
    char *tok = strtok(tmp, del);
    for (count = 0; tok != NULL; count++) {
        tok = strtok(NULL, del);
    }
    free(tmp);

    // now actually split str
    char **p = malloc((count + 1) * sizeof(char *));
    tok = strtok(str, del);
    for (int i = 0; i < count; i++) {
        p[i] = tok;
        tok = strtok(NULL, del);
    }
    // NULL terminate list
    p[count] = NULL;

    return p;
}

int argslen(char **args)
{
    int count = 0;
    for (char **p = args; *p != NULL; p++) {
        count++;
    }
    return count;
}
