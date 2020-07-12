#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define W 1280
#define H 1024

const double Y0 = -1.75;  /* Y is the real axis aligned vertically */
const double Y1 = 0.75;
const double X0 = -1.50; /* X is the imaginary axis aligned horizontally */
const double X1 = 1.50;
int count[W][H];

void orbit()
{
    complex double c;
    complex double z;

    for (int n = 0; n < 10000000; n++) {
        c = ((double)rand() / RAND_MAX * (Y1 - Y0) + Y0) +
            ((double)rand() / RAND_MAX * (X1 - X0) + X0)*I;
        z = 0;
        for (int i = 0; i < 1000; i++) {
            z = z * z + c;
            if (cabs(z) > 2.0) {
                /* this c escaped so let's reiterate the sequence 
                   recording counts this time */
                z = 0;
                while (cabs(z) <= 2.0) {
                    int yy = (creal(z) - Y0) / (Y1 - Y0) * H;
                    int xx = (cimag(z) - X0) / (X1 - X0) * W;
                    if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                        count[xx][yy]++;
                    }
                    z = z * z + c;
                }
                break;
            }
        }
    }
}

void clip(int threshold)
{
    int i, j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            double c = count[j][i] / (double)threshold;
            if (c > 1.0)
                c = 1.0;
            count[j][i] = c * 255.0;
        }
    }
}

void write_image()
{
    printf("P2\n");
    printf("%d %d\n255\n", W, H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%03d ", count[j][i]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int clip_th = 255;
    if (argc == 2) {
        clip_th = atoi(argv[1]);
    }
    orbit();
    clip(clip_th);
    write_image();

    return 0;
}
