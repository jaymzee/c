extern "C" {
#include "wavefmt.h"
}
#include "CanonicalFilter.h"
#include <cstdio>

CanonicalFilter fs = {
    {0.0, 0.0, 0.0},    //w
    {0.2, 0.2, 0.2},    //b
    {1.0, 0.3, 0.3}     //a
};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    for (double x : fs.w)
        printf("w: %g\n", x);
    for (double x : fs.b)
        printf("b: %g\n", x);
    for (double x : fs.a)
        printf("a: %g\n", x);

    return wavefmt_filter(argv[1], argv[2], 
                          CanonicalFilter::procsamp, &fs,
                          WAVEFMT_PCM, 0.0); 
}
