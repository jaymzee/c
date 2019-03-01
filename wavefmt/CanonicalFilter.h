#ifndef CANONICALFILTER_H
#define CANONICALFILTER_H

/* canonical filter for signal processing */

#include "filter.h"
#include <vector>

class CanonicalFilter {
public:
    std::vector<double> w;       /* delay line */
    std::vector<double> b;       /* b coefficients - feed forward */
    std::vector<double> a;       /* a coefficients - feedback */
    static filter_func procsamp; /* process one sample through filter */
};

#endif /* CANONICALFILTER_H */
