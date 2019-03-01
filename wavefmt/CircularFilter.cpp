#include "CircularFilter.h"
/*
 * CircularFilter::CircularFilter() - construct a CircularFilter
 * @length: length of delay line
 */
CircularFilter::CircularFilter(unsigned length) : w(length), offset(0)
{
}

/*
 * CircularFilter::operator--() - advance delay line by one sample
 *
 * Return: reference to *this
 */
CircularFilter& CircularFilter::operator--()
{
    if (--offset < 0)
        offset += w.size();
    return *this;
}

/*
 * CircularFilter::operator++() - retreat delay line by one sample
 *
 * Return: reference to *this
 */
CircularFilter& CircularFilter::operator++()
{
    unsigned N = w.size();
    if (++offset > N)
        offset -= N;
    return *this;
}

/*
 * CircularFilter::operator[]() - reference tap[n]
 *
 * Return: reference to tap[n] (offset and modulo wrap of w)
 */
double& CircularFilter::operator[](unsigned n)
{
    return w[(offset + n) % w.size()];
}

/*
 * CircularFilter::length() - length of delay line
 */
unsigned CircularFilter::length()
{
    return w.size();
}

/*
 * CircularFilter::procsamp() - process one sample
 * @x: input sample
 * @state: pointer to the state of the filter (CircularFilter)
 *
 * Return: output sample
 */
float CircularFilter::procsamp(float x, void *state)
{
    CircularFilter &fs = *(CircularFilter *)state;
    double y, w0;
    
    w0 = x;
    for (auto it : fs.a)
        w0 -= it.second * fs[it.first];
    fs[0] = w0;

    y = 0.0;
    for (auto it : fs.b) 
        y += it.second * fs[it.first];

    --fs;

    return y;
}
