#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define IMG_WIDTH  1024
#define IMG_HEIGHT 1280

const double X0 = -1.75;    /* X is the real axis aligned horizontally */
const double X1 =  0.75;
const double Y0 = -1.50;    /* Y is the imaginary axis aligned vertically */
const double Y1 =  1.50;

/* ESC_MAG for conventional mandelbrot rendering escape magnitude is usually 2.0, 
   (values outside this will always escape to infinity) but with buddhabrot method 
   setting this to 2.3 with the coordinates above avoids a harsh circle at the top edge (neg real axis) 

   things to try

   POINTS 10000000
   MAX_ITER 1000

   POINTS 5000000
   MAX_ITER 10000
*/
const double ESC_MAG = 2.3;
const int POINTS = 10000000;
const int MAX_ITER = 1000;

int count[IMG_HEIGHT][IMG_WIDTH];

void orbit()
{
    complex double c;
    complex double z;

    for (int n = 0; n < POINTS; n++) {
        c = ((double)rand() / RAND_MAX * (X1 - X0) + X0) +
            ((double)rand() / RAND_MAX * (Y1 - Y0) + Y0) * I;
        z = 0;
        for (int i = 0; i < MAX_ITER; i++) {
            z = z * z + c;
            if (cabs(z) > ESC_MAG) {
                /* this c escaped so let's reiterate the sequence 
                   recording counts this time */
                z = 0;
                while (cabs(z) <= ESC_MAG) {
                    /* map complex z back to image coordinates */
                    int x = (creal(z) - X0) / (X1 - X0) * IMG_WIDTH;
                    int y = (cimag(z) - Y0) / (Y1 - Y0) * IMG_HEIGHT;
                    if (x >= 0 && x < IMG_WIDTH && y >= 0 && y < IMG_HEIGHT) {
                        count[y][x]++;
                    }
                    z = z * z + c;
                }
                break;
            }
        }
    }
}

void write_image()
{
    printf("P2\n");
    printf("%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT);
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            printf("%03d ", count[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    orbit();
    write_image();

    return 0;
}
