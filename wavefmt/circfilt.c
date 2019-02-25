#include "circfilt.h"
#include <stdlib.h>
#include <string.h>

/*
 * circfilt_create() - allocate and initialize a circular filter
 * @N:      length of w
 * @Nb:     length of b;
 * @b_val:  b values;
 * @b_indx: b indices;
 * @Na:     length of a;
 * @a_val:  a values;
 * @a_indx: a indices;
 *
 * Return: the initialized state structure for the filter
 */
struct circfilt_state *
circfilt_create(unsigned N, unsigned Nb, unsigned *b_indx, double *b_val,
                            unsigned Na, unsigned *a_indx, double *a_val)
{
    struct circfilt_state *s;
    s = malloc(sizeof(struct circfilt_state));
    s->N = N;
    s->Na = Na;
    s->Nb = Nb;
    s->w = calloc(N, sizeof(double));
    s->a_indx = calloc(Na, sizeof(int));
    s->a_val  = calloc(Na, sizeof(double));
    s->b_indx = calloc(Nb, sizeof(int));
    s->b_val  = calloc(Nb, sizeof(double));
    memcpy(s->a_indx, a_indx, Na * sizeof(int));
    memcpy(s->a_val,  a_val,  Na * sizeof(double));
    memcpy(s->b_indx, b_indx, Nb * sizeof(int));
    memcpy(s->b_val,  b_val,  Nb * sizeof(double));
    s->offset = 0;
    return s;
}

/*
 * circfilt_destroy() - free memory allocated for circular filter
 * @s: pointer to filter state
 */
void circfilt_destroy(struct circfilt_state *s)
{
    free(s->b_val);
    free(s->b_indx);
    free(s->a_val);
    free(s->a_indx);
    free(s->w);
    free(s);
}

/*
 * circfilt_dec() - decrement offset of w buffer (advance delay line by one)
 * @s: pointer to filter state
 *
 * properly wrap offset so that it doesn't fall off the edge of buffer
 */
void circfilt_dec(struct circfilt_state *s)
{
    s->offset--;
    if (s->offset < 0)
        s->offset += s->N;
}

/*
 * circfilt_inc() - increment offset of w buffer
 * @s: pointer to filter state
 *
 * properly wrap offset so that it doesn't fall off the edge of buffer
 */
void circfilt_inc(struct circfilt_state *s)
{
    s->offset++;
    if (s->offset > s->N)
        s->offset -= s->N;
}

/*
 * circfilt_w() - return pointer to w[n] while handling wrapping
 * @s: pointer to filter state
 * @n: index into w
 *
 * Return: pointer to w[n]
 */
double * circfilt_w(struct circfilt_state *s, unsigned n)
{
    return s->w + ((s->offset + n) % s->N);
}

/*
 * circfilt_procsamp() - process one sample through the canonical filter
 * @x: input sample to process
 * @state: pointer to the state of the filter
 *
 * Return: output sample
 */
float circfilt_procsamp(float x, void *state)
{
    struct circfilt_state *fs = state;
    double y;
    double w0;
    unsigned n;

    w0 = x;
    for (n = 0; n < fs->Na; n++)
        w0 -= fs->a_val[n] * *circfilt_w(fs, fs->a_indx[n]);
    *circfilt_w(fs, 0) = w0;

    y = 0.0;
    for (n = 0; n < fs->Nb; n++)
        y += fs->b_val[n] * *circfilt_w(fs, fs->b_indx[n]);

    circfilt_dec(fs);

    return y;
}
