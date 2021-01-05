#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t shift_lfsr(uint64_t *lfsr, uint64_t poly)
{
    int fb = *lfsr & 1;

    *lfsr >>= 1;
    if (fb) {
        *lfsr ^= poly;
    }

    return *lfsr;
}

void run_lfsr(uint64_t iv, uint64_t poly)
{
    unsigned long long x = iv, period = 0;
    while (1) {
        if (period < 16) {
            printf("%d: %016llx\n", (int)(period+1), x);
        } else if (period == 16) {
            printf("...\n");
        }
        shift_lfsr(&iv, poly);
        period++;
        if (x == iv)
            break;
    }
    printf("period = %llu\n", period);
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
    run_lfsr(iv, poly);
}
