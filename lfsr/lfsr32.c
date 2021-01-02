#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void run_lfsr(uint32_t poly, uint32_t iv)
{
    uint32_t x = iv, period = 0;
    while (1) {
        if (period < 16) {
            printf("%4d: %08x\n", period+1, x);
        } else if (period == 16) {
            printf("...\n");
        }
        int fb = x & 1;
        x = x >> 1;
        if (fb)
            x ^= poly;
        period++;
        if (x == iv)
            break;
    }
    printf("period = %u\n", period);
}

int main(int argc, char *argv[])
{
    uint32_t poly, iv;

    if (argc != 3) {
        printf("Usage: lfsr poly iv\n\n");
        printf("examples:\n");
        printf("\tlfsr 9 1\n");
        printf("\tlfsr aa2255dd 1\n");
        exit(1);
    }
    poly = strtoul(argv[1], NULL, 16);
    iv = strtoul(argv[2], NULL, 16);
    run_lfsr(poly, iv);
}
