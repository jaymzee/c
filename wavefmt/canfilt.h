#ifndef CANFILT_H
#define CANFILT_H

/* canonical filter for signal processing */

#include "filter.h"

struct canfilt_state {
    double *w;      /* delay line */
    double *a;      /* a coefficients - feedback */
    double *b;      /* b coefficients - feed forward */
    unsigned N;     /* length of w, a, b */
};

/* allocate and initialize state object */
struct canfilt_state *
canfilt_create(unsigned N, double *b, double *a);

/* free state object */
void canfilt_destroy(struct canfilt_state *s);

/* process one sample through canonical filter */
filter_func canfilt_procsamp;

#endif /* CANFILT_H */
