#include "wavefmt.h"
#include "canfilt.h"
#include <stdio.h>

double b[3] = {0.2, 0.2, 0.2};
double a[3] = {1.0, 0.3, 0.3};

int main(int argc, char *argv[])
{
    struct canfilt_state *fs;
    
    fs = canfilt_create(3, b, a);

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    return wavefmt_filter(argv[1], argv[2], canfilt_procsamp, fs,
                          WAVEFMT_FLOAT, 4.0); 
}
