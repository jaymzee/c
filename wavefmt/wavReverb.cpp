extern "C" {
#include "wavefmt.h"
}
#include "CircularFilter.h"
#include <cstdio>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    CircularFilter fs(5000);
    fs.b[1] = 0.4;
    fs.b[3500] = 0.4;
    fs.a[3000] = 0.6;

    return wavefmt_filter(argv[1], argv[2], 
                          CircularFilter::procsamp, &fs,
                          WAVEFMT_PCM, 2.0); 
}
