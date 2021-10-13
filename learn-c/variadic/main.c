#include <stdarg.h>
#include <stdio.h>

int sum(int num, ...)
{
    va_list args;
    int sum = 0;

    /* initialize args to store all values after num */
    va_start(args, num);

    for (int i = 0; i < num; i++) {
        int x = va_arg(args, int);
        sum += x;
    }

    va_end(args);

    return sum;
}

void print_strings(const char *first, ...)
{
    va_list args;

    va_start(args, first);

    for (const char *s = first; s != NULL; s = va_arg(args, const char *)) {
        puts(s);
    }

    va_end(args);
}

int main()
{

    printf("%d\n", sum(3, 1, 2, 3));
    printf("%d\n", sum(4, 1, 2, 3, 4));
    print_strings("hey", "hi", "hello", (char *)0);

    return 0;
}
