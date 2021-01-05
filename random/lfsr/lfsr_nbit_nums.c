#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// only a single bit of an lfsr is pseudorandom!

uint32_t shift_lfsr(uint32_t *val, uint32_t poly)
{
    int fb = *val & 1;

    *val >>= 1;
    if (fb)
        *val ^= poly;

    return *val;
}

uint32_t get_random(uint32_t *iv, uint32_t lfsr_poly, int n)
{
    int result = 0;

    for (int i = 0; i < n; i++) {
        result = result << 1 | (shift_lfsr(iv, lfsr_poly) & 1);
    }

    return result;
}

int main(int argc, char *argv[])
{
    uint32_t poly, seed, n, x;

    if (argc != 4) {
        printf("Usage: lfsr poly iv bits\n\n");
        printf("examples:\n");
        printf("\tlfsr 9 1 4\n");
        printf("\tlfsr aa2255dd 1 32\n");
        exit(1);
    }
    poly = strtoul(argv[1], NULL, 16);
    seed = strtoul(argv[2], NULL, 16);
    n = strtoul(argv[3], NULL, 10);

    for (int i = 0; i < 16; i++) {
        x = get_random(&seed, poly, n);
        printf("x: %08x  seed: %08x\n", x, seed);
    }

    return 0;
}
