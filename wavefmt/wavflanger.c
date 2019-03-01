#include "wavefmt.h"
#include "fracdelay.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

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
    double y;
    double n;
    
    n = (N-1) * (0.5 * cos(2 * PI * fl->rate * fl->phase) + 0.5);

    *fracdelay_w0(delay) = x;

    y = 0.5 * fracdelay_w(delay, N / 2) + 0.5 * fracdelay_w(delay, n);

    fracdelay_dec(delay);
    fl->phase += 1.0 / 44100.0;

    return y;
}

int main(int argc, char *argv[])
{
    struct flanger fl;
    int rv;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavflanger infile outfile\n");
        return EXIT_FAILURE;
    }

    fl.rate = 0.125;
    fl.phase = 0.0;
    fl.delay = fracdelay_create(200);
    rv = wavefmt_filter(argv[1], argv[2], flanger_procsamp, &fl,
                        WAVEFMT_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
