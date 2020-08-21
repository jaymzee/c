#include <stdio.h>
#include <stdlib.h>

int main()
{
    //srand(42);
    unsigned int seed = 42;

    for (int i = 0; i < 10; i++) {
        int x = rand_r(&seed);
        printf("%d %u\n", x, seed);
    }
}
