#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "fft.h"

#define V_SIZE 8
double complex x[V_SIZE] = {1,2,3,4,3,2,1,0};
double complex y[V_SIZE];

void printcmplx(double complex x)
{
    printf("(%11.4e %+11.4ej)", creal(x), cimag(x));
}

void printvector(double complex *x, int length, char *name)
{
    for (int n = 0; n < length; n++) {
        printf("%s[%d] = ", name, n);
        printcmplx(x[n]);
        printf("\n");
    }
}

void test_dft()
{
    printf("Testing DFT...\n");
    printvector(x, V_SIZE, "x");

    dft(y, x, V_SIZE);

    printf("X = fft(x)\n");
    printvector(y, V_SIZE, "X");

    idft(x, y, V_SIZE);

    printf("x = ifft(X)\n");
    printvector(x, V_SIZE, "x");
}

void test_fft()
{
    printf("Testing FFT...\n");
    printvector(x, V_SIZE, "x");

    fft(y, x, V_SIZE);

    printf("X = fft(x)\n");
    printvector(y, V_SIZE, "X");

    ifft(x, y, V_SIZE);

    printf("x = ifft(X)\n");
    printvector(x, V_SIZE, "x");
}

void test_fft_iter()
{
    printf("Testing FFT_iterative_in_place...\n");
    printvector(x, V_SIZE, "x");

    shuffle(y, x, V_SIZE);
    fft_iter_ip(y, V_SIZE);

    printf("X = fft(x)\n");
    printvector(y, V_SIZE, "X");

    shuffle(x, y, V_SIZE);
    ifft_iter_ip(x, V_SIZE);

    printf("x = ifft(X)\n");
    printvector(x, V_SIZE, "x");
}

int main(int argc, char *argv[])
{
    test_dft();
    test_fft();
    test_fft_iter();
}
