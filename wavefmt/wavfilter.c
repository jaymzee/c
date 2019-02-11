#include "wavefmt.h"
#include <stdio.h>
#include <stdlib.h>

struct filterstate {
    double w[4000];
};

float fir(float x, void *state)
{
    struct filterstate *fs = state;
    double *w = fs->w;
    int n, N = (sizeof fs->w) / (sizeof *fs->w);
    double y;

    y = 0.5 * w[N - 1] + 0.5 * x;

    for (n = N - 1; n > 0; n--)
        w[n] = w[n - 1];

    w[0] = x;

    return y;
}

float iir(float x, void *state)
{
    struct filterstate *fs = state;
    double *w = fs->w;
    int n, N = (sizeof fs->w) / (sizeof *fs->w);
    double y;

    y = 0.2 * w[1500] + 0.2 * w[2000] + 0.2 * w[2500] + x;

    for (n = N - 1; n > 0; n--)
        w[n] = w[n - 1];

    w[0] = y;

    return y;
}

int main(int argc, char *argv[])
{
    struct filterstate *fs = calloc(1, sizeof(struct filterstate));

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    wavefmt_filter(argv[1], argv[2], iir, fs, WAVEFMT_FLOAT, 4.0); 

    return 0;
}
