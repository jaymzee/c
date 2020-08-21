#include <stdio.h>
#include <vector>

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

void dosomething(const std::vector<double>& nums, double f(double))
{
    int n = nums.size();
    printf("[");
    for (double num : nums)
        printf(--n != 0 ? "%g, " : "%g]\n", f(num));
}

int main()
{
    std::vector<double> nums = {1.1, 2.2, 3.3, 4.4};

    dosomething(nums, id);
    dosomething(nums, square);
    dosomething(nums, twice);
    dosomething(nums, half);

    return 0;
}
