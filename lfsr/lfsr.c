#include <stdio.h>
#include <stdint.h>

#define POLY 0xaa2255dd
#define IV 1

int main()
{
    uint32_t period = 0;
    uint32_t x = IV;

    while (1) {
        int fb = x & 1;
        x = x >> 1;
        if (fb)
            x ^= POLY;
        period++;
        if (x == IV)
            break;
    }

    printf("period = %u\n", period);
}
