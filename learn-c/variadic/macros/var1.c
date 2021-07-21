/* variadic macros */

#include <stdio.h>

#define PRINT(...) fprintf(stderr, __VA_ARGS__)
#define foo(m, n, ...) printf("1st = %d, 2nd = %d\n", m, n)
#define bar(m, ...) printf("1st = %d\n", m)
#define baz(_1, n, ...) printf("2nd = %d\n", n)

int main()
{
    PRINT("Hello, World!\n");
    foo(3, 4);
    foo(3, 4, 5);

    return 0;
}
