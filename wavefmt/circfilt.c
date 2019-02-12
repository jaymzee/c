#include "circfilt.h"
#include <stdlib.h>
#include <string.h>

struct circfilt_state *
circfilt_create(int N, int Nb, int *b_indx, double *b_val,
                       int Na, int *a_indx, double *a_val)
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

void circfilt_dec(struct circfilt_state *s)
{
    s->offset--;
    if (s->offset < 0)
        s->offset += s->N;
}

void circfilt_inc(struct circfilt_state *s)
{
    s->offset++;
    if (s->offset > s->N)
        s->offset -= s->N;
}

double * circfilt_w(struct circfilt_state *s, int n)
{
    return s->w + ((s->offset + n) % s->N);
}

float circfilt_procsamp(float x, void *state)
{
    struct circfilt_state *fs = state;
    double y;
    double w0;
    int n;

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
