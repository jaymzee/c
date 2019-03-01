#ifndef FRACDELAY_H
#define FRACDELAY_H

/*
 * circular buffer implementation of a fractional delay line 
 */

struct fracdelay_state {
    double *w;       /* delay line */
    unsigned N;      /* length of w */
    unsigned offset; /* current start of buffer within w */
};

/* allocate and initialize */
struct fracdelay_state *fracdelay_create(unsigned N);

/* free state object */
void fracdelay_destroy(struct fracdelay_state *s);

/* decrement offset within w buffer (advance delay line by one sample) */
void fracdelay_dec(struct fracdelay_state *s);

/* increment offset within w buffer */
void fracdelay_inc(struct fracdelay_state *s);

/* return w[n] while handling wrapping */
double fracdelay_w(struct fracdelay_state *s, double n);

/* return pointer to w[0] */
double *fracdelay_w0(struct fracdelay_state *s);

#endif /* FRACDELAY_H */
