#include "CanonicalFilter.h"

/*
 * CanonicalFilter::procsamp() - process one sample through canonical filter
 * @x: input sample to process
 * @state: pointer to the state of the filter (CanonicalFilter)
 *
 * Return: output sample
 */
float CanonicalFilter::procsamp(float x, void *state)
{
    CanonicalFilter &fs = *(CanonicalFilter *)state;
    double y, w0;

    w0 = x;
    for (int n = fs.a.size() - 1; n > 0; n--)
        w0 -= fs.a[n] * fs.w[n];
    fs.w[0] = w0;

    y = 0.0;
    for (int n = fs.b.size() - 1; n >= 0; n--)
        y += fs.b[n] * fs.w[n];

    for (int n = fs.w.size() - 1; n > 0; n--)
        fs.w[n] = fs.w[n - 1];

    return y;
}
