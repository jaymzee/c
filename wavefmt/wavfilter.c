#include "wavefmt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct circular_state {
    double N;
    double *w;
    double *a;
    double *b;
    int offset;
};

void circular_wrap()
{
    
}

struct canonical_state {
    double N;
    double *w;
    double *a;
    double *b;
};

struct canonical_state *
canonical_create(const int N, const double *b, const double *a)
{
    struct canonical_state *s;
    s = malloc(sizeof(struct canonical_state));
    s->N = N;
    s->w = calloc(N, sizeof(double));
    s->a = calloc(N, sizeof(double));
    s->b = calloc(N, sizeof(double));
    memcpy(s->a, a, N * sizeof(double));
    memcpy(s->b, b, N * sizeof(double));
    s->a[0] = 1.0;
    return s;
}

float canonical_filter(float x, void *state)
{
    const struct canonical_state *fs = state;
    const int N = fs->N;
    double *w = fs->w;
    double *a = fs->a;
    double *b = fs->b;
    double y;
    int n;

    w[0] = x;
    for (n = 1; n < N; n++)
        w[0] -= a[n] * w[n];

    y = 0.0;
    for (n = 0; n < N; n++)
        y += b[n] * w[n];

    for (n = N - 1; n > 0; n--)
        w[n] = w[n - 1];

    return y;
}

float reverb(float x, void *state)
{
    const struct circular_buffer *buf = state;
    const int N = buf->N;
    double y;
    int n;

    y = 0.2 * w[1500] + 0.2 * w[2000] + 0.2 * w[2500] + x;

    for (n = N - 1; n > 0; n--)
        w[n] = w[n - 1];

    w[0] = y;

    return y;
}

int main(int argc, char *argv[])
{
    double a[3] = {1.0, 0.3, 0.3};
    double b[3] = {0.2, 0.2, 0.2};
    struct canonical_state *state = canonical_create(3, b, a);

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    wavefmt_filter(argv[1], argv[2], canonical_filter, state, WAVEFMT_FLOAT, 4.0); 

    return 0;
}
