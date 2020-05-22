#include <math.h>
#include <complex.h>
#include "fft.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Discrete Fourier Transform
    N^2 time complexity
*/
void dft(double complex *out, const double complex *in, const int N)
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

/* Inverse Discrete Fourier Transform
    N^2 time complexity
*/
void idft(double complex *out, const double complex *in, const int N)
{
    const double complex W_N = cexp(I * 2 * M_PI / N);
    double complex W_k = 1;
    for (int k = 0; k < N; k++, W_k *= W_N) {
        double complex sum = 0;
        double complex W = 1;
        for (int n = 0; n < N; n++, W *= W_k) {
            sum += in[n] * W;
        }
        out[k] = sum / N;
    }
}

/* Fast Fourier Transform (recursion)
    X output array
    x input array
    N array length, must be a power of 2
    s stride
*/
static void
fft1(double complex *X, const double complex *x, const int N, const int s)
{
    if (N == 1) {
        X[0] = x[0];
        return;
    }
    fft1(X,       x,     N/2, 2 * s); // X[0]...X[N/2-1] <- DFT(evenish of x)
    fft1(X + N/2, x + s, N/2, 2 * s); // X[N/2]...X[N-1] <- DFT(oddish of x)
    for (int k = 0; k < N/2; k++) {
        double complex t = X[k];
        X[k]       = t + cexp(-I * 2 * M_PI * k / N) * X[k + N/2];
        X[k + N/2] = t - cexp(-I * 2 * M_PI * k / N) * X[k + N/2];
    }
}

/* Fast Fourier Transform (wrapper)
    recursive, decimation in time
    N log N time complexity

    X output array
    x input array
    N array length, must be a power of 2
*/
void fft(double complex *X, const double complex *x, const int N)
{
    fft1(X, x, N, 1);
}

/* Inverse Fast Fourier Transform (recursion)
    recursive, decimation in time

    X output array
    x input array
    N array length, must be a power of 2
    s stride
*/
static void
ifft1(double complex *x, const double complex *X, const int N, const int s)
{
    if (N == 1) {
        x[0] = X[0];
        return;
    }
    ifft1(x,       X,     N/2, 2 * s); // x[0]...x[N/2-1] <- IDFT(evenish of X)
    ifft1(x + N/2, X + s, N/2, 2 * s); // x[N/2]...x[N-1] <- IDFT(oddish of X)
    for (int k = 0; k < N/2; k++) {
        double complex t = x[k];
        x[k]       = t + cexp(I * 2 * M_PI * k / N) * x[k + N/2];
        x[k + N/2] = t - cexp(I * 2 * M_PI * k / N) * x[k + N/2];
    }
}

/* Inverse Fast Fourier Transform (wrapper)
    recursive, decimation in time

    X output array
    N array length, must be a power of 2
*/
void ifft(double complex *x, const double complex *X, const int N)
{
    ifft1(x, X, N, 1);
    for (int n = 0; n < N; n++) {
        x[n] /= N;
    }
}

/* w is the bit width of the index e.g. n=12 for N=4096 */
static unsigned int reverse_bits(register unsigned int x, int w)
{
    x = (x & 0xaaaaaaaa) >> 1 | (x & 0x55555555) << 1;
    x = (x & 0xcccccccc) >> 2 | (x & 0x33333333) << 2;
    x = (x & 0xf0f0f0f0) >> 4 | (x & 0x0f0f0f0f) << 4;
    x = (x & 0xff00ff00) >> 8 | (x & 0x00ff00ff) << 8;
    x = x >> 16 | x << 16;
    return x >> (32 - w);
}

/* array length N must be a power of 2 */
void shuffle(double complex *out, const double complex *in, const int N)
{
    int n = log2(N);
    for (int k = 0; k < N; ++k) {
        out[reverse_bits(k, n)] = in[k];
    }
}

/* Fast Fourier Transfrom
    iterative, in place, and decimation in time

    A complex array
    N array length must be a power of 2 
*/
void fft_iter_ip(double complex *A, const int N)
{
    const int log2N = log2(N);

    for (int s = 1; s <= log2N; ++s) {
        const int m = 1 << s;  // 2^s
        const double complex W_m = cexp(-I * 2 * M_PI / m);
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

/* Inverse Fast Fourier Transfrom
    decimation in time, iterative, and in place
    N log(N) time complexity

    A complex array
    N array length must be a power of 2
*/
void ifft_iter_ip(double complex *A, const int N)
{
    const int log2N = log2(N);

    for (int s = 1; s <= log2N; ++s) {
        const int m = 1 << s;  // 2^s
        const double complex W_m = cexp(I * 2 * M_PI / m);
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
    for (int n = 0; n < N; n++) {
        A[n] /= N;
    }
}

