#include <stdio.h>

typedef unsigned int uint;

typedef union port {
    unsigned char byte;
    struct bits {
        uint b7 : 1;
        uint b6 : 1;
        uint b5 : 1;
        uint b4 : 1;
        uint b3 : 1;
        uint b2 : 1;
        uint b1 : 1;
        uint b0 : 1;
    } bit;
} port;

int main()
{
    volatile port p1;

    p1.byte = 0x55;
    printf("hello %d\n", p1.bit.b3);
    printf("hello %d\n", p1.bit.b2);
    printf("hello %d\n", p1.byte);
}
