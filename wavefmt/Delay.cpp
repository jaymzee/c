#include "Delay.h"

/*
 * Delay::Delay() - construct a fractional delay line 
 * @length: length of delay line
 */
Delay::Delay(unsigned length) : w(length), offset(0)
{
}

/*
 * Delay::operator--() - advance delay line by one sample
 *
 * Return: reference to *this
 */
Delay& Delay::operator--()
{
    if (--offset < 0)
        offset += w.size();
    return *this;
}

/*
 * Delay::operator--() - retreat delay line by one sample
 *
 * Return: reference to *this
 */
Delay& Delay::operator++()
{
    unsigned N = w.size();
    if (++offset > N)
        offset -= N;
    return *this;
}

/*
 * Delay::operator[](double) - interpolate tap[n]
 * @n: index of delay line tap, must be >= 0 but may have a fractional part
 *
 * since there is a fractional part to n, linearly interpolate the samples
 *
 * Return: tap[n] (offset within and modulo wrap w)
 */
double Delay::operator[](double n)
{
    double w1, w2, f;
    unsigned N = w.size();
    int first = (int)n;

    w1 = w[(offset + first) % N];
    w2 = w[(offset + first + 1) % N];
    f = n - first;
    return (1.0 - f) * w1 + f * w2;
}

/*
 * Delay::operator[](int) - reference tap[n]
 * @n: index of delay line tap
 *
 * Return: reference to w[n] (offset within and modulo wrap w)
 */
double& Delay::operator[](int n)
{
    return w[(offset + n) % w.size()];
}

/*
 * Delay::length() - length of delay line
 */
unsigned Delay::length()
{
    return w.size();
}
