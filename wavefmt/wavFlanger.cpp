extern "C" {
#include "wavefmt.h"
}
#include "Delay.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define PI 3.14159265358979323846
#define FS 44100

struct Flanger
{
    double rate;
    double phase;
    Delay tap;
};

float flanger_procsamp(float x, void *state)
{
    Flanger &fl = *(Flanger *)state;
    const int N = fl.tap.length();
    const double n = (N - 1) * (0.5 * cos(2 * PI * fl.rate * fl.phase) + 0.5);
    double y;

    fl.tap[0] = x;
    y = 0.5 * fl.tap[N / 2] + 0.5 * fl.tap[n];
    --fl.tap;
    fl.phase += 1.0 / FS;

    return y;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavflanger infile outfile\n");
        return EXIT_FAILURE;
    }

    Flanger fl = {0.125, 0.0, Delay(200)};
    int rv = wavefmt_filter(argv[1], argv[2],
                            flanger_procsamp, &fl,
                            WAVEFMT_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
