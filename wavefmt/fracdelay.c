#include "fracdelay.h"
#include <stdlib.h>
#include <string.h>

/*
 * fracdelay_create() - allocate and initialize a fractional delay
 * @N:      length of w
 *
 * Return: the initialized state structure for the filter
 */
struct fracdelay_state *
fracdelay_create(unsigned N)
{
    struct fracdelay_state *s;
    s = malloc(sizeof(*s));
    s->N = N;
    s->w = calloc(N, sizeof(double));
    s->offset = 0;
    return s;
}

/*
 * fracdelay_destroy() - free memory allocated for circular filter
 * @s: pointer to filter state
 */
void fracdelay_destroy(struct fracdelay_state *s)
{
    free(s->w);
    free(s);
}

/*
 * fracdelay_dec() - decrement offset of w buffer 
 *                   (advance delay line by one sample)
 * @s: pointer to filter state
 *
 * properly wrap offset so that it doesn't fall off the edge of buffer
 */
void fracdelay_dec(struct fracdelay_state *s)
{
    if (s->offset == 0)
        s->offset = s->N; 
    s->offset--;
}

/*
 * circfilt_inc() - increment offset of w buffer
 * @s: pointer to filter state
 *
 * properly wrap offset so that it doesn't fall off the edge of buffer
 */
void fracdelay_inc(struct fracdelay_state *s)
{
    s->offset++;
    if (s->offset > s->N)
        s->offset -= s->N;
}

/*
 * fracdelay_w() - return pointer to w[n] while handling wrapping
 * @s: pointer to filter state
 * @n: index into w (must be positive or zero but can have a fractional part)
 *
 * since there is a fractional part to n, linearly interpolate the samples
 *
 * Return: w[n]
 */
double fracdelay_w(struct fracdelay_state *s, double n)
{
    double wa, wb, f;
    wa = s->w[(s->offset + (int)n) % s->N];
    wb = s->w[(s->offset + (int)(n+1)) % s->N];
    f = n - (int)n;
    return (1.0 - f) * wa + f * wb;
}

/*
 * fracdelay_w0() - return pointer to w[0]
 * @s: pointer to filter state
 *
 * Return: pointer to w[n]
 */
double *fracdelay_w0(struct fracdelay_state *s)
{
    return s->w + s->offset;
}
