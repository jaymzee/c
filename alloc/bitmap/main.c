#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define ALLOC_SIZE 1024
#define BITMAP_LENGTH 2048 // 64MB of memory

uint32_t bitmap[BITMAP_LENGTH];
void *memblk;

unsigned int log2i(unsigned int n)
{
    int i = 0;

    if (n < 1) {
        fprintf(stderr, "log2i(%d): math domain error", n);
        exit(1);
    }
    while (n >>= 1) {
        i++;
    }
    return i;
}

void *alloc(void)
{
    for (int i = 0; i < BITMAP_LENGTH; i++) {
        uint32_t bm = ~bitmap[i];
        uint32_t bitset = bm & -bm;
        if (bitset) {
            int bit = log2i(bitset);
            // printf("%02x %08x %u %d\n", bitmap[i], bm, bitset, bit);
            bitmap[i] |= bitset;
            return memblk + (32 * i + bit) * ALLOC_SIZE;
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    memblk = malloc(64 * 1024 * 1024);

    for (int i = 0; i < 40; i++) {
        void *p = alloc();
        if (p) {
            printf("%d\n", p - memblk);
        } else {
            printf("alloc failed\n");
        }
    }

    return 0;
}
