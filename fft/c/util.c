#include <stdio.h>
#include <complex.h>

void print_complex(double complex x, char format)
{
    switch (format) {
    case 'f': // fixed point
        if (cimag(x) < 0.0)
            printf("(%11.4f - %10.4fj)", creal(x), -cimag(x));
        else
            printf("(%11.4f + %10.4fj)", creal(x), cimag(x));
        break;
    case 'e': // scientific (exponential)
        if (cimag(x) < 0.0)
            printf("(%11.4e - %10.4ej)", creal(x), -cimag(x));
        else
            printf("(%11.4e + %10.4ej)", creal(x), cimag(x));
        break;
    case 'g': // general
    default:
        if (cimag(x) < 0.0)
            printf("(%g - %gj)", creal(x), -cimag(x));
        else
            printf("(%g + %4gj)", creal(x), cimag(x));
    }
}

void print_complex_array(double complex *x, int length,
                         const char *name, char format)
{
    for (int n = 0; n < length; n++) {
        printf("%s[%d] = ", name, n);
        print_complex(x[n], format);
        printf("\n");
    }
}

