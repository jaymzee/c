#include <stdlib.h>
#include <string.h>

struct circular_filter_state {
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

struct circular_filter_state *
circular_filter_create(int N, int Nb, int *b_indx, double *b_val,
                              int Na, int *a_indx, double *a_val)
{
    struct circular_state *s;
    s = malloc(sizeof(struct circular_state));
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

void circular_filter_dec(struct circular_filter_state *s)
{
    s->offset--;
    if (s->offset < 0)
        s->offset += s->N;
}

void circular_filter_inc(struct circular_filter_state *s)
{
    s->offset++;
    if (s->offset > s->N)
        s->offset -= s->N;
}

double * circular_filter_w(struct circular_state *s, int n)
{
    return s->w + ((s->offset + n) % s->N);
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
