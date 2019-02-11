#include "wavefmt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct circular_state {
    double *w;
    double *a_indx;
    double *a_val;
    double *b_indx;
    double *b_val;
    int offset;
    int N;
    int Na;
    int Nb;
};

struct circular_state *
circular_create(const int N, int Nb, int *b_indx, double *b_val,
                             int Na, int *a_indx, double *a_val)
{
    struct circular_state *s;
    s = malloc(sizeof(struct circular_state));
    s->N = N;
    s->w = calloc(N, sizeof(double));
    s->a_indx = calloc(Na, sizeof(int));
    s->a_val  = calloc(Na, sizeof(double));
    s->b_indx = calloc(Nb, sizeof(int));
    s->b_val  = calloc(Nb, sizeof(double));
    memcpy(s->a_indx, a_indx, Na * sizeof(int));
    memcpy(s->a_val,  a_val,  Na * sizeof(double));
    memcpy(s->b_indx, b_indx, Nb * sizeof(int));
    memcpy(s->b_val,  b_val,  Nb * sizeof(double));
    return s;
}

void circular_dec(struct circular_state *s)
{
    s->offset--;
    if (s->offset < 0)
        s->offset += s->N;
}

double * circular_w(struct circular_state *s, int n)
{
    return s->w + ((s->offset + n) % s->N);
}

struct canonical_state {
    double *w;
    double *a;
    double *b;
    int N;
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

float circular_filter(float x, void *state)
{
    struct circular_state *buf = state;
    double y;
    double w0;
    int n;

    w0 = x;
    for (n = 0; n < buf->Na; n++)
        w0 -= buf->a_val[n] * *circular_w(buf, buf->a_indx[n]);
    *circular_w(buf, 0) = w0;

    y = 0.0;
    for (n = 0; n < buf->Nb; n++)
        y += buf->b_val[n] * *circular_w(buf, buf->b_indx[n]);

    circular_dec(buf);

    return y;
}

int test_canonical(int argc, char *argv[])
{
    double a[3] = {1.0, 0.3, 0.3};
    double b[3] = {0.2, 0.2, 0.2};
    struct canonical_state *can = canonical_create(3, b, a);

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    return wavefmt_filter(argv[1], argv[2], canonical_filter, can, WAVEFMT_FLOAT, 4.0); 
}

int test_circular(int argc, char *argv[])
{
    int    b_indx[2] = {1000, 2000};
    double b_val[2]  = {0.4, 0.4};
    int    a_indx[2] = {1000, 2000};
    double a_val[2]  = {0.4, 0.4};
    struct circular_state *circ = circular_create(3000, 2, b_indx, b_val,
                                                        2, a_indx, a_val);

    if (argc != 3) {
        fprintf(stderr, "Usage: filter infile outfile\n");
        return -1;
    }

    return wavefmt_filter(argv[1], argv[2], circular_filter, circ, WAVEFMT_FLOAT, 4.0); 
}

int main(int argc, char *argv[])
{
#ifndef CAN    
    return test_canonical(argc, argv); 
#else
    return test_circular(argc, argv);
#endif
}
