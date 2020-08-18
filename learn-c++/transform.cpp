#include <cstdio>
#include <vector>
#include <algorithm>

typedef double funcd1d(double x);
typedef double funcd2d(double x, double y);

funcd1d id, square, twice, half;

double id(double x)
{
    return x;
}

double square(double x)
{
    return x * x;
}

double twice(double x)
{
    return 2 * x;
}

double half(double x)
{
    return x / 2;
}

void map_then_print(const std::vector<double>& nums, funcd1d f)
{
    int n = nums.size();
    if (n == 0)
        printf("[]\n");
    else
        printf("[");
    for (double num : nums)
        printf(--n != 0 ? "%g, " : "%g]\n", f(num));
}

int main()
{
    std::vector<double> x = {1.1, 2.2, 3.3, 4.4};
    std::vector<double> y(4);

    std::transform(x.begin(), x.end(), y.begin(), square);
    printf("x = ");
    map_then_print(x, square);
    printf("y = ");
    map_then_print(y, id);

    return 0;
}

