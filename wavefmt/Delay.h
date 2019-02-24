#ifndef DELAY_H
#define DELAY_H

#include <vector>

/*
 * circular buffer implementation of a fractional delay line (CPP) 
 */

class Delay {
    std::vector<double> w;  /* delay line */
    int offset;             /* current start of buffer within w */
public:
    Delay(int length);
    Delay& operator--();    /* (advance delay line by one sample) */
    Delay& operator++();    /* (retreat delay line by one sample) */
    double operator[](double n);    /* interpolate w[n] */
    double& operator[](int n);      /* reference to w[n] */
    int length();           /* length of delay line */
};

#endif /* DELAY_H */
