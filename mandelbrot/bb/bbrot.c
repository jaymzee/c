#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>

/*
   X0,Y0,X1,Y1 define the coordinate range (lower left to upper right) of the region to render
   ESCAPE_MAG for a conventional mandelbrot rendering is usually 2.0 (values outside this always escape to infinity)
   but for buddhabrot method setting this to 2.3 with the coordinates above avoids a harsh circle at the edge

   things to try:

   1280 x 1024
   samples  10000000
   max_iter 1000

   samples  5000000
   max_iter 10000
*/

const double X0 = -1.70;    /* X is the real axis aligned horizontally */
const double X1 =  0.75;
const double Y0 = -1.50;    /* Y is the imaginary axis aligned vertically */
const double Y1 =  1.50;
const double ESCAPE_MAG = 2.3;

void render_image(int *count, int width, int height, int samples, int max_iter)
{
    complex double c;
    complex double z;

    for (int n = 0; n < samples; n++) {
        c = ((double)rand() / RAND_MAX * (X1 - X0) + X0) +
            ((double)rand() / RAND_MAX * (Y1 - Y0) + Y0) * I;
        z = 0;
        for (int i = 0; i < max_iter; i++) {
            z = z * z + c;
            if (cabs(z) > ESCAPE_MAG) {
                /* this c escaped so let's reiterate the sequence 
                   recording counts this time */
                z = 0;
                while (cabs(z) <= ESCAPE_MAG) {
                    /* map complex z back to image coordinates */
                    int x = (creal(z) - X0) / (X1 - X0) * width;
                    int y = (cimag(z) - Y0) / (Y1 - Y0) * height;
                    if (x >= 0 && x < width && y >= 0 && y < height) {
                        count[y * width + x]++;
                    }
                    z = z * z + c;
                }
                break;
            }
        }
    }
}

void write_image(int *count, int width, int height, int samples, int max_iter)
{
    printf("# Buddhabrot rendering\n");
    printf("# image size: %d x %d \n", width, height);
    printf("# samples: %d \n", samples);
    printf("# max iterations: %d \n", max_iter);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%03d ", count[i * width + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int max_iter = 20;
    int width = 64;
    int height = 64;
    int samples = 1000;

    /* process command line arguments */
    for (int i = 1; i < argc; i++) {
        if (strncmp("-m", argv[i], 2) == 0) {
            max_iter = atoi(argv[i] + 2);
        }
        if (strncmp("-s", argv[i], 2) == 0) {
            samples = atoi(argv[i] + 2);
        }
        if (strncmp("-w", argv[i], 2) == 0) {
            width = atoi(argv[i] + 2);
        }
        if (strncmp("-h", argv[i], 2) == 0) {
            height = atoi(argv[i] + 2);
        }
    }

    int *count = calloc(width * height, sizeof(*count));

    /* render image */
    render_image(count, width, height, samples, max_iter);

    /* write image data to stdout */
    write_image(count, width, height, samples, max_iter);

    free(count);

    return 0;
}
