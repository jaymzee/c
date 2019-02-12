#include "wavefmt.h"
#include <stdio.h>

int    b_indx[2] = {1, 3500};
double b_val[2]  = {0.4, 0.4};
int    a_indx[1] = {3000};
double a_val[1]  = {0.6};

int main(int argc, char *argv[])
{
    struct circular_filter_state *fs;
    
    fs = circular_filter_create(5000, 2, b_indx, b_val, 2, a_indx, a_val);

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }
    
    return wavefmt_filter(argv[1], argv[2], circular_filter, fs,
                          WAVEFMT_FLOAT, 4.0); 
}
