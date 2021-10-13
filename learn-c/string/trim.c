#include <ctype.h>
#include <string.h>

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
