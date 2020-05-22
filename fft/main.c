#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "fft.h"

#define FIXED 1
#define EXP 0
#define V_SIZE 8
double complex x[V_SIZE] = {1,2,3,4,3,2,1,0};
double complex X[V_SIZE];

void print_complex(double complex x, int fmt)
{
    if (fmt) {
        if (cimag(x) < 0.0)
            printf("(%11.4f - %10.4fj)", creal(x), -cimag(x));
        else
            printf("(%11.4f + %10.4fj)", creal(x), cimag(x));
    } else {
        if (cimag(x) < 0.0)
            printf("(%11.4e - %10.4ej)", creal(x), -cimag(x));
        else
            printf("(%11.4e + %10.4ej)", creal(x), cimag(x));
    }
}

void print_complex_array(double complex *x, int length, char *name, int fmt)
{
    for (int n = 0; n < length; n++) {
        printf("%s[%d] = ", name, n);
        print_complex(x[n], fmt);
        printf("\n");
    }
}

void show_dft(int fmt)
{
    printf("Testing dft...\n");
    print_complex_array(x, V_SIZE, "x", fmt);

    dft(X, x, V_SIZE);

    printf("X = dft(x)\n");
    print_complex_array(X, V_SIZE, "X", fmt);

    idft(x, X, V_SIZE);

    printf("x = idft(X)\n");
    print_complex_array(x, V_SIZE, "x", fmt);
}

void show_fft_rec(int fmt)
{
    printf("Testing fft_rec (dit, recursive)...\n");
    print_complex_array(x, V_SIZE, "x", fmt);

    fft_rec(X, x, V_SIZE);

    printf("X = fft_rec(x)\n");
    print_complex_array(X, V_SIZE, "X", fmt);

    ifft_rec(x, X, V_SIZE);

    printf("x = ifft_rec(X)\n");
    print_complex_array(x, V_SIZE, "x", fmt);
}

void show_fft_iter(int fmt)
{
    printf("Testing fft_iter (dit, iterative, in place)...\n");
    print_complex_array(x, V_SIZE, "x", fmt);

    shuffle(X, x, V_SIZE);
    fft_iter(X, V_SIZE);

    printf("X = fft_iter(x)\n");
    print_complex_array(X, V_SIZE, "X", fmt);

    shuffle(x, X, V_SIZE);
    ifft_iter(x, V_SIZE);

    printf("x = ifft_iter(X)\n");
    print_complex_array(x, V_SIZE, "x", fmt);
}

void benchmark_dft(int loops)
{
    printf("running dft, N=%d, %d times (slowest)...", V_SIZE, loops);
    fflush(stdout);
    for (int n = 0; n < loops; n++) {
        dft(X, x, V_SIZE);
    }
    printf("done\n");
}

void benchmark_fft_rec(int loops)
{
    printf("running fft_rec (recursive), N=%d, %d times (fast)...",
           V_SIZE, loops);
    fflush(stdout);
    for (int n = 0; n < loops; n++) {
        fft_rec(X, x, V_SIZE);
    }
    printf("done\n");
}

void benchmark_fft_iter(int loops)
{
    printf("running fft_iter (iterative, in place) "
           "N=%d, %d times (fastest)...", V_SIZE, loops);
    fflush(stdout);
    for (int n = 0; n < loops; n++) {
        shuffle(X, x, V_SIZE);
        fft_iter(X, V_SIZE);
    }
    printf("done\n");
}

int main(int argc, char *argv[])
{
    if (V_SIZE <= 256) {
        show_dft(FIXED);
        show_fft_rec(FIXED);
        show_fft_iter(FIXED);
    }

    benchmark_dft(10);
    benchmark_fft_rec(1000);
    benchmark_fft_iter(1000);
}
