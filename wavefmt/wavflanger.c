#include "wavefmt.h"
#include "fracdelay.h"
#include <stdio.h>


float flanger_procsamp(float x, void *state)
{
    struct fracdelay_state *fs = state;
    const int N = fs->N;
    double *w = fs->w;
    double y;
    double n = 900.5;
    
    w[0] = x;

    y = x + fracdelay_w(fs, n);

    return y;
}

int main(int argc, char *argv[])
{
    struct fracdelay_state *fs;
    
    fs = fracdelay_create(1000);

    if (argc != 3) {
        fprintf(stderr, "Usage: wavflanger infile outfile\n");
        return -1;
    }

    return wavefmt_filter(argv[1], argv[2], flanger_procsamp, fs,
                          WAVEFMT_PCM, 0.0); 
}
