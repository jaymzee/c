#include "wavefmt.h"
#include "circfilt.h"
#include <stdio.h>

int    b_indx[2] = {1, 3500};
double b_val[2]  = {0.4, 0.4};
int    a_indx[1] = {3000};
double a_val[1]  = {0.6};

int main(int argc, char *argv[])
{
    struct circfilt_state *fs;
    
    fs = circfilt_create(5000, 2, b_indx, b_val, 2, a_indx, a_val);

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }
    
    return wavefmt_filter(argv[1], argv[2], circfilt_procsamp, fs,
                          WAVEFMT_PCM, 2.0); 
}
