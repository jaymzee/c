#include <cstdio>
#include <complex>
#include "fft.hpp"
#include "util.hpp"

#define V_SIZE 8

std::complex<double> x[V_SIZE] = {1,2,3,4,3,2,1,0};
std::complex<double> X[V_SIZE];

void show_dft(int fmt)
{
    printf("Testing dft...\n");
    util::print(std::cout, x, V_SIZE, "x", fmt);

    fft::dft(X, x, V_SIZE);

    printf("X = dft(x)\n");
    util::print(std::cout, X, V_SIZE, "X", fmt);

    fft::idft(x, X, V_SIZE);

    printf("x = idft(X)\n");
    util::print(std::cout, x, V_SIZE, "x", fmt);
}

void show_fft_rec(int fmt)
{
    printf("Testing fft_rec (dit, recursive)...\n");
    util::print(std::cout, x, V_SIZE, "x", fmt);

    fft::fft_rec(X, x, V_SIZE);

    printf("X = fft_rec(x)\n");
    util::print(std::cout, X, V_SIZE, "X", fmt);

    fft::ifft_rec(x, X, V_SIZE);

    printf("x = ifft_rec(X)\n");
    util::print(std::cout, x, V_SIZE, "x", fmt);
}

void show_fft_iter(int fmt)
{
    printf("Testing fft_iter (dit, iterative, in place)...\n");
    util::print(std::cout, x, V_SIZE, "x", fmt);

    fft::shuffle(X, x, V_SIZE);
    fft::fft_iter(X, V_SIZE);

    printf("X = fft_iter(x)\n");
    util::print(std::cout, X, V_SIZE, "X", fmt);

    fft::shuffle(x, X, V_SIZE);
    fft::ifft_iter(x, V_SIZE);

    printf("x = ifft_iter(X)\n");
    util::print(std::cout, x, V_SIZE, "x", fmt);
}

int main(int argc, char *argv[])
{
    if (V_SIZE <= 256) {
        show_dft('f');
        show_fft_rec('f');
        show_fft_iter('f');
    }
}
