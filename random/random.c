#include <stdio.h>

int my_rand (unsigned int *seed)
{
  unsigned int next = *seed;
  int result;

  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;

  *seed = next;

  return result;
}

int main()
{
    unsigned int iv = 42, seed = iv;
    unsigned int period = 0;

    my_rand(&seed);

    while (1) {
        my_rand(&seed);
        period++;
        if (seed == iv)
            break;
    }
    printf("%u\n", period);
}
