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

struct image {
    int *buffer;
    int width;
    int height;
};

void render_orbits(const struct image *img, int samples, int max_iter)
{
    complex double z, c;
    int *const buf = img->buffer;
    const int w = img->width;
    const int h = img->height;

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
                    int x = (creal(z) - X0) / (X1 - X0) * w;
                    int y = (cimag(z) - Y0) / (Y1 - Y0) * h;
                    if (x >= 0 && x < w && y >= 0 && y < h) {
                        buf[y * w + x]++;
                    }
                    z = z * z + c;
                }
                break;
            }
        }
    }
}

void write_image(const struct image *img, int samples, int max_iter)
{
    int *const buf = img->buffer;
    const int w = img->width;
    const int h = img->height;

    printf("# Buddhabrot rendering\n");
    printf("# image size: %d x %d \n", w, h);
    printf("# samples: %d \n", samples);
    printf("# max iterations: %d \n", max_iter);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf("%03d ", buf[y * w + x]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    struct image img = { NULL, 64, 64 };
    int max_iter = 20;
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
            img.width = atoi(argv[i] + 2);
        }
        if (strncmp("-h", argv[i], 2) == 0) {
            img.height = atoi(argv[i] + 2);
        }
    }

    img.buffer = calloc(img.width * img.height, sizeof(*img.buffer));
    render_orbits(&img, samples, max_iter);
    write_image(&img, samples, max_iter);
    free(img.buffer);

    return 0;
}
