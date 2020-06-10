#include <stdio.h>
#include <complex.h>
#include "fft.h"
#include "util.h"

#define V_SIZE 4096
double complex x[V_SIZE];
double complex X[V_SIZE];

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
    //benchmark_dft(10);
    //benchmark_fft_rec(1000);
    benchmark_fft_iter(10000);
}
