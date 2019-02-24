#include "Delay.h"

/*
 * Delay::Delay() - construct a fractional delay line 
 * @length: length of delay line
 */
Delay::Delay(int length) : w(length), offset(0)
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
    const int N = w.size();
    if (++offset > N)
        offset -= N;
    return *this;
}

/*
 * Delay::operator[](double) - interpolate w[n] while handling wrapping
 * @n: index into delay line, must be >= 0 but may have a fractional part
 *
 * since there is a fractional part to n, linearly interpolate the samples
 *
 * Return: w[n]
 */
double Delay::operator[](double n)
{
    double w1, w2, f;
    const int N = w.size();
    const int first = (int)n;

    w1 = w[(offset + first) % N];
    w2 = w[(offset + first + 1) % N];
    f = n - first;
    return (1.0 - f) * w1 + f * w2;
}

/*
 * Delay::operator[](int) - reference w[n] while handling wrapping
 * @n: index into delay line
 *
 * Return: reference to w[n]
 */
double& Delay::operator[](int n)
{
    return w[(offset + n) % w.size()];
}

/*
 * Delay::length() - length of delay line
 */
int Delay::length()
{
    return w.size();
}
