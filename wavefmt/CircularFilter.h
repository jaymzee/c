#ifndef CIRCULARFILTER_H
#define CIRCULARFILTER_H

/* 
 * circular buffer implementation of a canonical filter (CPP)
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse thus filtering is very efficient if most
 * the values for a and b are zero.
 */

#include "filter.h"
#include <vector>
#include <map>

class CircularFilter {
    std::vector<double> w;          /* delay line */
    int offset;                     /* current start of buffer within w */
public:
    std::map<int, double> a;        /* feedback coefficients */
    std::map<int, double> b;        /* feedforward coefficients */
    CircularFilter(int length);
    CircularFilter& operator--();   /* advance delay line by one sample */
    CircularFilter& operator++();   /* retreat delay line by one sample */
    double& operator[](int n);      /* reference to w[n] */
    int length();                   /* length of delay line */
    static filter_func procsamp;    /* process one sample through filter */
};

#endif /* CIRCULARFILTER_H */
