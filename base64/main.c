#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    const char *filename;
    unsigned char *data;
    char *encoded;
    size_t len, encoded_len;
    int wrap = 72;

    /* process command line args */
    if (argc < 2) {
        printf("Usage: base64 [-w COLS] FILE\n");
        exit(2);
    }
    filename = argv[argc - 1];
    if (argc >= 3 && strncmp(argv[1], "-w", 2) == 0) {
        wrap = atoi(argv[2]);
    }

    /* read the file into memory */
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0L, SEEK_END);
    len = ftell(fp);
    rewind(fp);
    data = malloc(len);
    if (data == NULL) {
        perror("failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    if (fread(data, 1, len, fp) != len) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    /* base64 encode the file */
    encoded = base64_encode(data, len, wrap, &encoded_len);

    // printf("length: %zu (%zu encoded)\n", len, encoded_len);
    printf("%s", encoded);

    free(encoded);
    free(data);

    exit(EXIT_SUCCESS);
}
