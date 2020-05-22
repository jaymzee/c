#ifndef UTIL_H
#define UTIL_H

#include <complex.h>

void print_complex(double complex x, char format);

void print_complex_array(double complex *x, int length,
                         const char *name, char fmt);

#endif /* UTIL_H */
