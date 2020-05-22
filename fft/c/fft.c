#include <math.h>
#include <complex.h>
#include "fft.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double complex twiddle(int N)
{
    return cexp(I * 2 * M_PI / N);
}

/* Discrete Fourier Transform
    N^2 time complexity
*/
void dft(double complex *X, const double complex *x, const int N)
{
    const double complex W_N = twiddle(-N);
    double complex W_k = 1, sum, W;
    for (int k = 0; k < N; k++, W_k *= W_N) {
        sum = 0;
        W = 1;
        for (int n = 0; n < N; n++, W *= W_k) {
            sum += x[n] * W;
        }
        X[k] = sum;
    }
}

/* Inverse Discrete Fourier Transform
    N^2 time complexity
*/
void idft(double complex *x, const double complex *X, const int N)
{
    const double complex W_N = twiddle(N);
    double complex W_k = 1, sum, W;
    for (int k = 0; k < N; k++, W_k *= W_N) {
        sum = 0;
        W = 1;
        for (int n = 0; n < N; n++, W *= W_k) {
            sum += X[n] * W;
        }
        x[k] = sum / N;
    }
}

/* Fast Fourier Transform (recursion)
    X output array
    x input array
    N array length, must be a power of 2
    s stride
*/
static void
fft_r(double complex *X, const double complex *x, const int N, const int s)
{
    if (N == 1) {
        X[0] = x[0];
        return;
    }

    fft_r(X,       x,     N/2, 2*s); // X[0]...X[N/2-1] <- DFT(evenish of x)
    fft_r(X + N/2, x + s, N/2, 2*s); // X[N/2]...X[N-1] <- DFT(oddish of x)

    const double complex W_N = twiddle(-N);
    double complex W = 1;
    for (int k = 0; k < N/2; k++, W *= W_N) {
        double complex t = X[k];
        X[k]       = t + W * X[k + N/2];
        X[k + N/2] = t - W * X[k + N/2];
    }
}

/* Fast Fourier Transform (wrapper)
    recursive, decimation in time
    N log N time complexity

    X output array
    x input array
    N array length, must be a power of 2
*/
void fft_rec(double complex *X, const double complex *x, const int N)
{
    fft_r(X, x, N, 1);
}

/* Inverse Fast Fourier Transform (recursion)
    X output array
    x input array
    N array length, must be a power of 2
    s stride
*/
static void
ifft_r(double complex *x, const double complex *X, const int N, const int s)
{
    if (N == 1) {
        x[0] = X[0];
        return;
    }

    ifft_r(x,       X,     N/2, 2*s); // x[0]...x[N/2-1] <- IDFT(evenish of X)
    ifft_r(x + N/2, X + s, N/2, 2*s); // x[N/2]...x[N-1] <- IDFT(oddish of X)

    const double complex W_N = twiddle(N);
    double complex W = 1;
    for (int k = 0; k < N/2; k++, W *= W_N) {
        double complex t = x[k];
        x[k]       = t + W * x[k + N/2];
        x[k + N/2] = t - W * x[k + N/2];
    }
}

/* Inverse Fast Fourier Transform (wrapper)
    recursive

    X output array
    N array length, must be a power of 2
*/
void ifft_rec(double complex *x, const double complex *X, const int N)
{
    ifft_r(x, X, N, 1);
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
    const int w = log2(N);

    if (out != in) {
        // assume distinct non-overlapping arrays
        for (int k = 0; k < N; ++k) {
            out[reverse_bits(k, w)] = in[k];
        }
    } else {
        // out and in are the same array
        for (int a = 0; a < N; ++a) {
            const int b = reverse_bits(a, w);
            if (a < b) {
                // swap out[b] with out[a]
                const double complex t = out[b];
                out[b] = out[a];
                out[a] = t;
            }
        }
    }
}

/* Fast Fourier Transfrom
    iterative, in place
    N log N time complexity

    x complex array
    N array length must be a power of 2
*/
void fft_iter(double complex *x, const int N)
{
    const int log2N = log2(N);
    double complex W, t, u;

    for (int s = 1; s <= log2N; ++s) {
        const int m = 1 << s;  // 2^s
        const double complex W_m = twiddle(-m);
        for (int k = 0; k < N; k += m) {
            W = 1;
            for (int j = 0; j < m/2; ++j, W *= W_m) {
                t = x[k + j];
                u = W * x[k + j + m/2];
                x[k + j] = t + u;
                x[k + j + m/2] = t - u;
            }
        }
    }
}

/* Inverse Fast Fourier Transfrom
    iterative, in place
    N log N time complexity

    X complex array
    N array length must be a power of 2
*/
void ifft_iter(double complex *X, const int N)
{
    const int log2N = log2(N);
    double complex W, t, u;

    for (int s = 1; s <= log2N; ++s) {
        const int m = 1 << s;  // 2^s
        const double complex W_m = twiddle(m);
        for (int k = 0; k < N; k += m) {
            W = 1;
            for (int j = 0; j < m/2; ++j, W *= W_m) {
                t = X[k + j];
                u = W * X[k + j + m/2];
                X[k + j] = t + u;
                X[k + j + m/2] = t - u;
            }
        }
    }
    for (int n = 0; n < N; n++) {
        X[n] /= N;
    }
}

