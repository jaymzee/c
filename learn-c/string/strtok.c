#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        char *str = argv[1];
        for (char *s = strtok(str, ","); s != NULL; s = strtok(NULL, ",")) {
            printf("'%s'\n", s);
        }
    }

    return 0;
}
