#include <stdio.h>

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

void dosomething(double num[], unsigned int N, funcd1d f)
{
    printf("[");
    while (N--)
        printf(N != 0 ? "%g, " : "%g]\n", f(*num++));
}

int main()
{
    double nums[] = {1.1, 2.2, 3.3, 4.4};

    double half();

    half(3.2);

    dosomething(nums, 4, id);
    dosomething(nums, 4, square);
    dosomething(nums, 4, twice);
    dosomething(nums, 4, half);

    return 0;
}
