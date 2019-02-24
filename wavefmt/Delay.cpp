#include "Delay.h"

Delay::Delay(int N) : w(N), offset(0)
{
}

Delay& Delay::operator--()
{
    if (--offset < 0)
        offset += w.size();
    return *this;
}

Delay& Delay::operator++()
{
    const int N = w.size();
    if (++offset > N)
        offset -= N;
    return *this;
}

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

double& Delay::operator[](int n)
{
    return w[(offset + n) % w.size()];
}

int Delay::length()
{
    return w.size();
}
