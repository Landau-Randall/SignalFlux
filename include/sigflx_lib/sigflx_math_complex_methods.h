#pragma once

#include "sigflx_lib/sigflx_math_complex.h"
#include <limits>

namespace SignalFlux
{
namespace Math
{
template<typename T>
bool isReal(const Complex<T> & object);

template<typename T>
bool isImaginary(const Complex<T> & object);

template<typename T>
bool isZero(const Complex<T> & object);

template<typename T>
T abs(const Complex<T> & z);

template<typename T>
T norm(const Complex<T> & z);

template<typename T>
Complex<T> polar(T radius,T theta);

template<typename T>
Complex<T> exp(const Complex<T> & z);

template<typename T>
Complex<T> ln(const Complex<T> & z);

template<typename T>
Complex<T> log2(const Complex<T> & z);

template<typename T>
Complex<T> log10(const Complex<T> & z);

template<typename T>
Complex<T> pow(const Complex<T> & z,T n);

template<typename T>
Complex<T> sqrt(const Complex<T> & z);

template<typename T>
Complex<T> sin(const Complex<T> & z);

template<typename T>
Complex<T> cos(const Complex<T> & z);

template<typename T>
Complex<T> tan(const Complex<T> & z);

template<typename T>
Complex<T> cot(const Complex<T> & z);

template<typename T>
Complex<T> sec(const Complex<T> & z);

template<typename T>
Complex<T> csc(const Complex<T> & z);

template<typename T>
Complex<T> asin(const Complex<T> & z);

template<typename T>
Complex<T> acos(const Complex<T> & z);

template<typename T>
Complex<T> atan(const Complex<T> & z);

template<typename T>
Complex<T> sinh(const Complex<T> & z);

template<typename T>
Complex<T> cosh(const Complex<T> & z);

template<typename T>
Complex<T> tanh(const Complex<T> & z);
}
}

#include "../../src/sigflx_lib/sigflx_math_complex_methods.tpp"