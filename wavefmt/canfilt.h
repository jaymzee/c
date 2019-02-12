#ifndef CANFILT_H
#define CANFILT_H

/* canonical filter for signal processing */

#include "filter.h"

struct canfilt_state {
    double *w;
    double *a;
    double *b;
    int N;
};

struct canfilt_state *canfilt_create(int N, double *b, double *a);

filter_func canfilt_procsamp;

#endif /* CANFILT_H */
