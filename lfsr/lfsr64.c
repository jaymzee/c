#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void run_lfsr(uint64_t poly, uint64_t iv)
{
    uint64_t x = iv, period = 0;
    while (1) {
        if (period < 16) {
            printf("%d: %016llx\n", (int)(period+1), (unsigned long long)x);
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
    printf("period = %llu\n", (unsigned long long)period);
}

int main(int argc, char *argv[])
{
    uint64_t poly, iv;

    if (argc != 3) {
        printf("Usage: lfsr poly iv\n\n");
        printf("examples:\n");
        printf("\tlfsr 9 1\n");
        printf("\tlfsr aa2255dd 1\n");
        exit(1);
    }
    poly = strtoull(argv[1], NULL, 16);
    iv = strtoull(argv[2], NULL, 16);
    run_lfsr(poly, iv);
}
