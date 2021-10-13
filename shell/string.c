#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

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

/*

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

// modifies string
char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

// modifies string
char *trim(char *s)
{
    return rtrim(ltrim(s));
}

*/
