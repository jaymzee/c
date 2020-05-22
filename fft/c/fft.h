#ifndef FFT_H
#define FFT_H

#include <complex.h>

/* Discrete Fourier Transform
    N^2 time complexity
*/
void dft(double complex *X, const double complex *x, int N);

/* Inverse Discrete Fourier Transform
    N^2 time complexity
*/
void idft(double complex *x, const double complex *X, int N);


/* Fast Fourier Transform
    recursive, decimation in time
    N log N time complexity

   X destination array
   x source array
   N array length, must be a power of 2
*/
void fft_rec(double complex *X, const double complex *x, int N);

/* Fast Fourier Transform
    recursive, decimation in time
    N log N time complexity

   X destination array
   x source array
   N array length, must be a power of 2
*/
void ifft_rec(double complex *x, const double complex *X, int N);


/* array length N must be a power of 2 */
void shuffle(double complex *out, const double complex *in, int N);

/* Fast Fourier Transfrom
    iterative, in place, decimation in time
    N log(N) time complexity

    x array to process
    N array length, must be a power of 2
*/
void fft_iter(double complex *x, int N);

/* Inverse Fast Fourier Transfrom
    iterative, in place, decimation in time
    N log(N) time complexity

    X array to process
    N array length, must be a power of 2
*/
void ifft_iter(double complex *X, int N);

#endif /* FFT_H */
