#include <iostream>
#include <vector>
#include "fft-vector.hpp"
#include "util.hpp"

typedef std::vector<std::complex<double>> vec_type;

vec_type x = {1,2,3,4,3,2,1,0};

int main()
{
    printf("fft_iter...\n");
    print_vector(std::cout, x, "x");

    vec_type y = fft_iter(x);
    print_vector(std::cout, y, "X");

    vec_type x2 = ifft_iter(y);
    print_vector(std::cout, x2, "x");
}
