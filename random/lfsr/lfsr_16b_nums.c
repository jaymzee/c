/*
 * this code is based on
 * APPLICATION NOTE 4400
 * RANDOM NUMBER GENERATION USING LFSR
 * https://www.maximintegrated.com/en/design/technical-documents/app-notes/4/4400.html
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define POLY_MASK_32 0xB4BCD35C
#define POLY_MASK_31 0x7A5BC2E3

uint32_t lfsr32 = 0xABCDE;
uint32_t lfsr31 = 0x23456789;

// only a bit is random of an lfsr
uint32_t shift_lfsr(uint32_t *lfsr, uint32_t poly)
{
    int fb = *lfsr & 1;

    *lfsr >>= 1;
    if (fb) {
        *lfsr ^= poly;
    }

    return *lfsr;
}

uint32_t get_random(void)
{
    /* This random number generator shifts the 32-bit LFSR twice before
     * XORing it with the 31-bit LFSR.  The bottom 16 bits are used for
     * the random number. */
    shift_lfsr(&lfsr32, POLY_MASK_32);
    return (shift_lfsr(&lfsr32, POLY_MASK_32) ^
            shift_lfsr(&lfsr31, POLY_MASK_31)) & 0xffff;
}

int main(int argc, char *argv[])
{
    uint32_t x;

    for (int i = 0; i < 16; i++) {
        x = get_random();
        printf("x: %08x  lfsr31: %08x  lfsr32: %08x\n", x, lfsr31, lfsr32);
    }

    return 0;
}
