#include "wavefmt.h"
#include <stdio.h>

float filter(float x, void *state)
{
    return x;
}

int main(int argc, char *argv[])
{
    int x;

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    /* wavefmt_filter(argv[1], argv[2], filter, &x, WAVEFMT_PCM, 0.0); */
    wavefmt_filter(argv[1], argv[2], filter, &x, WAVEFMT_FLOAT, 1.5); 

    return 0;
}
