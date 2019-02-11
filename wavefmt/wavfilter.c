#include "wavefmt.h"
#include <stdio.h>
#include <stdlib.h>

struct filterstate {
    double w[5];
};

float filter(float x, void *state)
{
    struct filterstate *fs = state;
    double *w = fs->w;
    int N = (sizeof fs->w) / (sizeof *fs->w);
    double y;

    y = 0.5 * w[4] + 0.5 * x;

    w[4] = w[3];
    w[3] = w[2];
    w[2] = w[1];
    w[1] = w[0];
    w[0] = x;

    return y;
}

int main(int argc, char *argv[])
{
    struct filterstate *fs = calloc(1, sizeof(struct filterstate));

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    wavefmt_filter(argv[1], argv[2], filter, fs, WAVEFMT_FLOAT, 4.0); 

    return 0;
}
