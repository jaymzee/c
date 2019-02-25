extern "C" {
#include "wavefmt.h"
}
#include "Delay.h"
#include <cstdio>
#include <cmath>

#define PI 3.141592654

struct Flanger
{
    double rate;
    double phase;
    Delay delay;
};

float flanger_procsamp(float x, void *state)
{
    Flanger &fl = *(Flanger *)state;
    Delay &delay = fl.delay;
    int N = delay.length();
    double n = (N-1) * (0.5 * cos(2 * PI * fl.rate * fl.phase) + 0.5);
    double y;

    delay[0] = x;
    y = 0.5 * delay[N / 2] + 0.5 * delay[n];
    --delay;
    fl.phase += 1.0 / 44100.0;

    return y;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavflanger infile outfile\n");
        return -1;
    }

    Flanger fl = {0.125, 0.0, Delay(200)};

    return wavefmt_filter(argv[1], argv[2], flanger_procsamp, &fl,
                          WAVEFMT_PCM, 0.0); 
}
