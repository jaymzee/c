#ifndef DELAY_H
#define DELAY_H

#include <vector>

/*
 * circular buffer implementation of a fractional delay line (CPP) 
 */

class Delay {
    std::vector<double> w;       /* delay line */
    unsigned offset;             /* current start of buffer within w */
public:
    Delay(unsigned length);
    Delay& operator--();         /* (advance delay line by one sample) */
    Delay& operator++();         /* (retreat delay line by one sample) */
    double operator[](double n); /* interpolate tap[n] */
    double& operator[](int n);   /* reference to tap[n] */
    unsigned length();           /* length of delay line */
};

#endif /* DELAY_H */
