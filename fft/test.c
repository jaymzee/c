#include <stdio.h>
#include <complex.h>
#include "fft.h"
#include "util.h"

#define V_SIZE 8
double complex x[V_SIZE] = {1,2,3,4,3,2,1,0};
double complex X[V_SIZE];

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

int main(int argc, char *argv[])
{
    if (V_SIZE <= 256) {
        show_dft('f');
        show_fft_rec('f');
        show_fft_iter('f');
    }
}
