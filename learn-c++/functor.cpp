#include <stdio.h>

class Mult {
private:
    double z;
public:
    Mult(double z) : z(z) { }
    double operator()(double x) { return z * x; }
};

int main()
{
    double nums[] = {1.1, 2.2, 3.3, 4.4};
    double z = 0.0;

    Mult mult(2.7);

    for (int n; n < 4; n++) {
        z += mult(nums[n]);
    }

    printf("result: %g\n", z);

    return 0;
}
