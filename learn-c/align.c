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

    return 0;
}
