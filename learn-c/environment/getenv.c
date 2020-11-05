#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
    // print environment
    for (char **p = envp; *p != NULL; p++) {
        printf("%s\n", *p);
    }

    // lookup single environment variable
    const char *val = getenv("FOO");
    if (val) {
        printf("%s\n", val);
    } else {
        printf("FOO not set\n");
    }
}
