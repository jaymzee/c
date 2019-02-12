#include "canfilt.h"
#include <stdlib.h>
#include <string.h>

struct canfilt_state *
canfilt_create(int N, double *b, double *a)
{
    struct canfilt_state *s;
    s = malloc(sizeof(struct canfilt_state));
    s->N = N;
    s->w = calloc(N, sizeof(double));
    s->a = calloc(N, sizeof(double));
    s->b = calloc(N, sizeof(double));
    memcpy(s->a, a, N * sizeof(double));
    memcpy(s->b, b, N * sizeof(double));
    s->a[0] = 1.0;
    return s;
}

float canfilt_procsamp(float x, void *state)
{
    const struct canfilt_state *fs = state;
    const int N = fs->N;
    double *w = fs->w;
    double *a = fs->a;
    double *b = fs->b;
    double y;
    double w0;
    int n;

    w0 = x;
    for (n = 1; n < N; n++)
        w0 -= a[n] * w[n];
    w[0] = w0;

    y = 0.0;
    for (n = 0; n < N; n++)
        y += b[n] * w[n];

    for (n = N - 1; n > 0; n--)
        w[n] = w[n - 1];

    return y;
}