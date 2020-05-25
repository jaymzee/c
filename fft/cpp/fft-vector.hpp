#ifndef FFT_VECTOR_H
#define FFT_VECTOR_H

#include <complex>
#include <vector>
#include "fft.hpp"

namespace fft
{

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
fft_iter(std::vector<std::complex<T>> x)
{
    const int N = x.size();
    shuffle(x.data(), x.data(), N);
    fft_iter(x.data(), N);
    return x;
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
ifft_iter(std::vector<std::complex<T>> X)
{
    const int N = X.size();
    shuffle(X.data(), X.data(), N);
    ifft_iter(X.data(), N);
    return X;
}

} /* namespace fft */

#endif /* FFT_VECTOR_H */
