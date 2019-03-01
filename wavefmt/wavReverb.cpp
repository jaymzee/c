extern "C" {
#include "wavefmt.h"
}
#include "CircularFilter.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavReverb infile outfile\n");
        return EXIT_FAILURE;
    }

    CircularFilter fs(5000);
    fs.b[1] = 0.4;
    fs.b[3500] = 0.4;
    fs.a[3000] = 0.6;

    int rv = wavefmt_filter(argv[1], argv[2], 
                            CircularFilter::procsamp, &fs,
                            WAVEFMT_PCM, 2.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
