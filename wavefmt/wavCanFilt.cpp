extern "C" {
#include "wavefmt.h"
}
#include "CanonicalFilter.h"
#include <cstdio>
#include <cstdlib>

CanonicalFilter fs = {
    {0.0, 0.0, 0.0},    //w
    {0.2, 0.2, 0.2},    //b
    {1.0, 0.3, 0.3}     //a
};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavCanFilt infile outfile\n");
        return EXIT_FAILURE;
    }

    int rv = wavefmt_filter(argv[1], argv[2], 
                            CanonicalFilter::procsamp, &fs,
                            WAVEFMT_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
