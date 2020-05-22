#ifndef UTIL_H
#define UTIL_H

#include <cstdio>
#include <iostream>
#include <complex>
#include <vector>

template <class T>
void print_complex(const std::complex<T>& x, char format)
{
    switch (format) {
    case 'f': // fixed point
        if (x.imag() < 0.0)
            printf("(%11.4f - %10.4fj)", x.real(), -x.imag());
        else
            printf("(%11.4f + %10.4fj)", x.real(), x.imag());
        break;
    case 'e': // scientific (exponential)
        if (x.imag() < 0.0)
            printf("(%11.4e - %10.4ej)", x.real(), -x.imag());
        else
            printf("(%11.4e + %10.4ej)", x.real(), x.imag());
        break;
    case 'g': // general
        if (x.imag() < 0.0)
            printf("(%g - %gj)", x.real(), -x.imag());
        else
            printf("(%g + %4gj)", x.real(), x.imag());
    default:
        std::cout << x;
    }
}

template <class T>
void print_complex_array(const std::complex<T> *x,
                         int length,
                         const char *name,
                         char fmt)
{
    for (int n = 0; n < length; n++) {
        printf("%s[%d] = ", name, n);
        print_complex(x[n], fmt);
        printf("\n");
    }
}

template <class T>
void print_complex_vector(const std::vector<std::complex<T>>& x,
                          const char *name,
                          char fmt)
{
    print_complex_array(x.data(), x.size(), name, fmt);
}

template <class T>
std::ostream& print_vector(std::ostream& os,
                           const std::vector<T>& v,
                           const char *name)
{
    int n = 0;
    for (auto e : v) {
        os << "name [" << n << "] = " << e << " " << std::endl;
        n++;
    }
    return os;
}

#endif
