#ifndef UTIL_H
#define UTIL_H

#include <cstdio>
#include <iostream>
#include <complex>
#include <vector>

namespace util
{

/* print vector of anything */
template <class T>
void print(std::ostream& os, const std::vector<T>& v,
           const char *name )
{
    int n = 0;
    for (auto e : v) {
        os << "name [" << n << "] = " << e << std::endl;
        n++;
    }
}

/* print complex */
template <class T>
std::ostream& print(std::ostream& os,
                    const std::complex<T>& x,
                    char format = 's')
{
    char buf[256];

    switch (format) {
    case 'f': // fixed point
        if (x.imag() < 0.0)
            sprintf(buf, "(%11.4f - %10.4fj)", x.real(), -x.imag());
        else
            sprintf(buf, "(%11.4f + %10.4fj)", x.real(), x.imag());
        os << buf;
        break;
    case 'e': // scientific (exponential)
        if (x.imag() < 0.0)
            sprintf(buf, "(%11.4e - %10.4ej)", x.real(), -x.imag());
        else
            sprintf(buf, "(%11.4e + %10.4ej)", x.real(), x.imag());
        os << buf;
        break;
    case 'g': // general
        if (x.imag() < 0.0)
            sprintf(buf, "(%g - %gj)", x.real(), -x.imag());
        else
            sprintf(buf, "(%g + %4gj)", x.real(), x.imag());
        os << buf;
        break;
    default:
        os << x;
    }
    return os;
}

/* print array of complex */
template <class T>
void print(std::ostream& os, const std::complex<T> *x,
           int length, const char *name, char fmt = 's')
{
    for (int n = 0; n < length; n++) {
        os << name << "[" << n << "] = ";
        if (fmt == 's') {
            os << x[n] << std::endl;
        } else {
            print(os, x[n], fmt) << std::endl;
        }
    }
}

/* print vector of complex */
template <class T>
void print(std::ostream& os, const std::vector<std::complex<T>>& v,
           const char *name, char fmt = 's')
{
    print(os, v.data(), v.size(), name, fmt);
}

} /* namespace util */

#endif
