#include <cstdio>
#include <iostream>

constexpr unsigned int factorial_ce(unsigned int n)
{
    return n == 0 ? 1 : n * factorial_ce(n - 1);
}

template <unsigned int n>
struct factorial {
    enum { value = n * factorial<n - 1>::value };
};

template <>
struct factorial<0> {
    enum { value = 1 };
};

int main(int argc, char *argv[])
{
    std::cout << "factorial<5> = " << factorial<5>::value << std::endl;
    std::cout << "factorial_ce(5) = " << factorial_ce(5) << std::endl;
}
