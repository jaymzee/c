#include "wavefmt.h"
#include <stdio.h>

float filter(float x)
{
    return x;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    wavefmt_filter(argv[1], argv[2], filter);

    return 0;
}
