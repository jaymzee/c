#include <stdio.h>
#include <math.h>
#include <complex.h>

/* w is the bit width of the index e.g. n=12 for N=4096 */
unsigned int
reverse_bits(register unsigned int x, int w)
{
    x = (x & 0xaaaaaaaa) >> 1 | (x & 0x55555555) << 1;
    x = (x & 0xcccccccc) >> 2 | (x & 0x33333333) << 2;
    x = (x & 0xf0f0f0f0) >> 4 | (x & 0x0f0f0f0f) << 4;
    x = (x & 0xff00ff00) >> 8 | (x & 0x00ff00ff) << 8;
    x = x >> 16 | x << 16;
    return x >> (32 - w);
}

/* Discrete Fourier Transform
    N^2 time complexity
*/
void dft(const double complex *in, double complex *out, int N)
{
    const double complex W_N = cexp(-I * 2 * M_PI / N);
    double complex W_k = 1;
    for (int k = 0; k < N; k++, W_k *= W_N) {
        double complex sum = 0;
        double complex W = 1;
        for (int n = 0; n < N; n++, W *= W_k) {
            sum += in[n] * W;
        }
        out[k] = sum;
    }
}

/* array length N must be a power of 2 */
void shuffle(const double complex *in, double complex *out, int N)
{
    int n = log2(N);
    for (int k = 0; k < N; ++k) {
        out[reverse_bits(k, n)] = in[k];
    }
}

/* Fast Fourier Transfrom
    N log(N) time complexity

    A complex array
    N array length must be a power of 2
*/
void fft_ip(double complex *A, int N)
{
    const int log2N = log2(N);

    for (int s = 1; s <= log2N; ++s) {
        const int m = 1 << s;  // 2^s
        const double complex W_m = cexp(-I * 2 * M_PI / m); // twiddle factor
        for (int k = 0; k < N; k += m) {
            double complex W = 1;
            for (int j = 0; j < m / 2; ++j, W *= W_m) {
                double complex t = W * A[k + j + m / 2];
                double complex u = A[k + j];
                A[k + j] = u + t;
                A[k + j + m / 2] = u - t;
            }
        }
    }
}

void printcmplx(double complex x)
{
    printf("(%10.3g %+10.3gI)", creal(x), cimag(x));
}

#define V_SIZE 8
double complex x[V_SIZE] = {1,2,3,4,3,2,1,0};
double complex y[V_SIZE];

int main()
{
    shuffle(x, y, V_SIZE);
    fft_ip(y, V_SIZE);

    for (int i = 0; i < 8; i++) {
        printcmplx(y[i]);
        printf(" ");
    }
    printf("\n");
}
