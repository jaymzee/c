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
    double *w;          /* delay line */
    double *a_val;      /* a coefficient values */
    double *b_val;      /* b coefficient values */
    unsigned *a_indx;   /* a coefficient index */
    unsigned *b_indx;   /* b coefficient index */
    unsigned Na;        /* length of a */
    unsigned Nb;        /* length of b */
    unsigned N;         /* length of w */
    unsigned offset;    /* current start of buffer within w */
};

/* allocate and initialize */
struct circfilt_state *
circfilt_create(unsigned N, unsigned Nb, unsigned *b_indx, double *b_val,
                            unsigned Na, unsigned *a_indx, double *a_val);

/* free state object */
void circfilt_destroy(struct circfilt_state *s);

/* decrement offset within w buffer (advance delay line by one) */
void circfilt_dec(struct circfilt_state *s);

/* increment offset within w buffer */
void circfilt_inc(struct circfilt_state *s);

/* return pointer to w[n] while handling wrapping */
double * circfilt_w(struct circfilt_state *s, unsigned n);

/* process one sample through circular filter */
filter_func circfilt_procsamp;

#endif /* CIRCFILT_H */
