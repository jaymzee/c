#ifndef FFT_H
#define FFT_H

#include <complex.h>

/* Discrete Fourier Transform
    N^2 time complexity
*/
void dft(double complex *out, const double complex *in, int N);

/* Inverse Discrete Fourier Transform
    N^2 time complexity
*/
void idft(double complex *out, const double complex *in, int N);


/* Fast Fourier Transform
    recursive, decimation in time
    N log N time complexity

   X destination array
   x source array
   N array length, must be a power of 2
*/
void fft(double complex *X, const double complex *x, int N);

/* Fast Fourier Transform
    recursive, decimation in time
    N log N time complexity

   X destination array
   x source array
   N array length, must be a power of 2
*/
void ifft(double complex *x, const double complex *X, int N);


/* array length N must be a power of 2 */
void shuffle(double complex *out, const double complex *in, int N);

/* Fast Fourier Transfrom
    iterative, in place, decimation in time
    N log(N) time complexity

    A array to process
    N array length, must be a power of 2
*/
void fft_iter_ip(double complex *A, int N);

/* Inverse Fast Fourier Transfrom
    iterative, in place, decimation in time
    N log(N) time complexity

    A array to process
    N array length, must be a power of 2
*/
void ifft_iter_ip(double complex *A, int N);

#endif /* FFT_H */
