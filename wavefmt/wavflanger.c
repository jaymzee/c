#include "wavefmt.h"
#include "fracdelay.h"
#include <stdio.h>
#include <math.h>

#define PI 3.141592654

struct flanger
{
    double rate;
    double phase;
    struct fracdelay_state *delay;
};

float flanger_procsamp(float x, void *state)
{
    struct flanger *fl = state;
    struct fracdelay_state *delay = fl->delay;
    const int N = delay->N;
    double *w = delay->w;
    double y;
    double n;
    
    n = N * (0.5 * cos(2 * PI * fl->rate * fl->phase) + 0.5);
    
    w[0] = x;

    y = 0.5 * x + 0.5 * fracdelay_w(delay, n);

    fracdelay_dec(delay);
    fl->phase += 1.0 / 44100.0;

    return y;
}

int main(int argc, char *argv[])
{
    struct flanger fl;

    fl.rate = 1.0;
    fl.phase = 0.0;
    fl.delay = fracdelay_create(1000);

    if (argc != 3) {
        fprintf(stderr, "Usage: wavflanger infile outfile\n");
        return -1;
    }

    return wavefmt_filter(argv[1], argv[2], flanger_procsamp, &fl,
                          WAVEFMT_PCM, 0.0); 
}
