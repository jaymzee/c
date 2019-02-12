#ifndef CIRCFILT_H
#define CIRCFILT_H

/*
 * circular buffer implementation of a canonical filter 
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse thus filtering is very efficient if most
 * the values for a and b are zero.
 */

#include "filter.h"

struct circfilt_state {
    double *w;
    double *a_val;
    double *b_val;
    int *a_indx;
    int *b_indx;
    int Na;
    int Nb;
    int N;
    int offset;
};

struct circfilt_state *
circfilt_create(int N, int Nb, int *b_indx, double *b_val,
                       int Na, int *a_indx, double *a_val);

void circfilt_dec(struct circfilt_state *s);
void circfilt_inc(struct circfilt_state *s);

double * circfilt_w(struct circfilt_state *s, int n);

filter_func circfilt_procsamp;

#endif /* CIRCFILT_H */
