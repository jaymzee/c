#include <iostream>
#include <vector>
#include "fft-vector.hpp"
#include "util.hpp"

typedef std::vector<std::complex<double>> vec_type;

vec_type x = {1,2,3,4,3,2,1,0};

int main()
{
    printf("fft_iter...\n");
    util::print(std::cout, x, "x");

    vec_type y = fft::fft_iter(x);
    util::print(std::cout, y, "X");

    vec_type x2 = fft::ifft_iter(y);
    util::print(std::cout, x2, "x");
}
