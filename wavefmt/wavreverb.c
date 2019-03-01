#include "wavefmt.h"
#include "circfilt.h"
#include <stdio.h>
#include <stdlib.h>

unsigned b_indx[2] = {1, 3500};
double   b_val[2]  = {0.4, 0.4};
unsigned a_indx[1] = {3000};
double   a_val[1]  = {0.6};

int main(int argc, char *argv[])
{
    struct circfilt_state *fs;
    int rv;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: wavreverb infile outfile\n");
        return EXIT_FAILURE;
    }

    fs = circfilt_create(5000, 2, b_indx, b_val, 2, a_indx, a_val);
    rv = wavefmt_filter(argv[1], argv[2], circfilt_procsamp, fs,
                        WAVEFMT_PCM, 2.0); 

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
