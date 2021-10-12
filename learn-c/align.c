/*
 * C11 has the _Alignas keyword and defines alignas as a preprocessor macro
 * expanding to the keyword in the header <stdalign.h>
 *
 * Syntax
 *  alignas(expression)
 *  alignas(type-id)
 *  alignas(pack...)
 */

#include <stdio.h>
#include <stdalign.h>

alignas(16) char a;
alignas(16) char b;
alignas(16) char c;

struct foo {
    alignas(2 * sizeof(void *))
    char x;
};

struct foo y, z;

int main()
{
    printf("a: %p\n", &a);
    printf("b: %p\n", &b);
    printf("c: %p\n", &c);

    printf("%d\n", sizeof(struct foo));
    printf("y: %p\n", &y);
    printf("z: %p\n", &z);

    printf("char: %d %d\n", sizeof(char), alignof(char));
    printf("int: %d %d\n", sizeof(int), alignof(int));
    printf("double: %d %d\n", sizeof(double), alignof(double));
    printf("void *: %d %d\n", sizeof(void *), alignof(void *));

    return 0;
}
