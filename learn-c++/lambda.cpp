#include <iostream>
#include <vector>
#include <algorithm> // for sort, unique, distance
#include <numeric> // for accumulate

/* closure using lambda */
auto foo(int x)
{
    return [=](int y) -> int { return x * y; };
}

int main()
{
    {
        // closure
        auto f = foo(2);
        std::cout << "closure: 2 * 3 = " << f(3) << std::endl;
    }
    {
        // sorting
        std::cout << "sorting a vector" << std::endl;
        std::vector<std::string> names = {
            "joe", "steve", "bill", "bob",
            "george", "john", "kevin"
        };
        for (auto name : names)
            std::cout << name << std::endl;
        std::cout << "sorting..." << std::endl;
        // std::sort(names.begin(), names.end());
        std::sort(names.begin(), names.end(),
            [](const std::string& a, const std::string& b) { return a > b; });
        for (auto name : names)
            std::cout << name << std::endl;
    }
    {
        std::cout << "unique" << std::endl;
        std::vector<int> v = { 1,2,3,4,4,5,5,5,6 };
        //std::unique(v.begin(), v.end());
        auto p = std::unique(v.begin(), v.end(),
                             [](int a, int b) { return a == b; });
        v.resize(std::distance(v.begin(), p));
        for (auto x : v)
            std::cout << x << std::endl;
    }
    {
        std::cout << "accumulate" << std::endl;
        std::vector<int> xs(5);
        std::iota(xs.begin(), xs.end(), 1);
        int f = std::accumulate(xs.begin(), xs.end(), 1,
                           [](int a, int b) -> int { return a * b; });
        for (auto x : xs)
            std::cout << x << std::endl;
        std::cout << "5! = " << f << std::endl;
    }
}
