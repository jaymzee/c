#include <stdio.h>

/* horner evaluates a length n polynomial p at the value x */
double horner(const double *p, int n, const double x)
{
    double a = 0.0;

    for (; n > 0; --n)
        a = a * x + *p++;

    return a;
}

/* polynomials are just arrays of the coefficients */

const double p1[] = {1, 3, 2};
double p2[] = {1, -3, 2};

int main()
{
    printf("poly1(2.7) = %g\n", horner(p1, 3, 2.7));
    printf("poly2(5) = %g\n", horner(p2, 3, 5));
}
