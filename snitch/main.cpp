#include <iostream>
#include <vector>
#include "Snitch.h"

std::vector<Snitch> f(int n)
{
    std::vector<Snitch> xs;
    xs.reserve(n);

    for (int k = 0; k < n; k++)
        xs.push_back(Snitch(k));

    return xs;
}

Snitch f()
{
    Snitch a(1);
    std::cout << &a << std::endl;
    return a;
}

Snitch g()
{
    return f();
}

int main()
{
    Snitch::disable_log();
    auto xs = f(4);
    Snitch::enable_log();
    auto ys = std::vector<Snitch>(4,0);
    Snitch::disable_log();
}
