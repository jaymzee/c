#include "wavefmt.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    char *filename;
    int rv;

    if (argc != 2) {
        fprintf(stderr, "Usage: wavdump wavfile\n");
        return EXIT_FAILURE;
    }

    filename = argv[1];
    rv = wavefmt_dump(filename);

    return (rv == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
