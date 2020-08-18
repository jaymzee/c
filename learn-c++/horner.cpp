#include <iostream>
#include <vector>

/* horner evaluates polynomial p at the value x */
template <class T>
T horner(const std::vector<T>& p, T x)
{
    T a{}; //initialize accumulator to zero

    for (auto coef : p)
        a = a * x + coef;

    return a;
}

/* polynomials are just vectors of the coefficients */

const std::vector<double> p1 {1, 3, 2};
const std::vector<int> p2 {1, -3, 2};

int main()
{
    std::cout << "p1(2.7) = " << horner(p1, 2.7) << std::endl;
    std::cout << "p2(5) = " << horner(p2, 5) << std::endl;
}
