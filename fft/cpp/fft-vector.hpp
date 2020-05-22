#ifndef FFT_VECTOR_H
#define FFT_VECTOR_H

#include <complex>
#include <vector>
#include "fft.hpp"

/* vector functions for working with vectors */

/* Discrete Fourier Transform (vector)
    N^2 time complexity

    x input vector
      vector length must be a power of 2
    returns transformed vector X
*/
template <class T>
std::vector<std::complex<T>>
dft(const std::vector<std::complex<T>>& x)
{
    const int N = x.size();
    std::vector<std::complex<T>> X(N);
    dft(X.data(), x.data(), N);
    return X;
}

/* Inverse Discrete Fourier Transform (vector)
    N^2 time complexity

    X input vector
      vector length must be a power of 2
    returns transformed vector x
*/
template <class T>
std::vector<std::complex<T>>
idft(const std::vector<std::complex<T>>& X)
{
    const int N = X.size();
    std::vector<std::complex<T>> x(N);
    idft(x.data(), X.data(), N);
    return x;
}

/* Fast Fourier Transform (vector)
    recursive, decimation in time
    N log N time complexity

    x input vector
      vector length must be a power of 2
    returns transformed vector X
*/
template <class T>
std::vector<std::complex<T>>
fft_rec(const std::vector<std::complex<T>>& x)
{
    const int N = x.size();
    std::vector<std::complex<T>> X(N);
    fft_rec(X.data(), x.data(), N);
    return X;
}

/* Inverse Fast Fourier Transform (vector)
    recursive
    N log N time complexity

    X input vector
      vector length must be a power of 2
    returns transformed vector x
*/
template <class T>
std::vector<std::complex<T>>
ifft_rec(const std::vector<std::complex<T>>& X)
{
    const int N = X.size();
    std::vector<std::complex<T>> x(N);
    ifft_rec(x.data(), X.data(), N);
    return x;
}

/* Fast Fourier Transfrom (vector)
    iterative, in place
    N log N time complexity

    x complex vector
      vector length must be a power of 2
    returns transformed vector X
*/
template <class T>
std::vector<std::complex<T>>
fft_iter(const std::vector<std::complex<T>>& x)
{
    const int N = x.size();
    std::vector<std::complex<T>> X(N);
    shuffle(X.data(), x.data(), N);
    fft_iter(X.data(), N);
    return X;
}

/* Inverse Fast Fourier Transfrom (vector)
    iterative, in place
    N log N time complexity

    X complex vector
      vector length must be a power of 2
    returns transformed vector x
*/
template <class T>
std::vector<std::complex<T>>
ifft_iter(const std::vector<std::complex<T>>& X)
{
    const int N = X.size();
    std::vector<std::complex<T>> x(N);
    shuffle(x.data(), X.data(), N);
    ifft_iter(x.data(), N);
    return x;
}

#endif /* FFT_VECTOR_H */
