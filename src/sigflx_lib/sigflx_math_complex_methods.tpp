#include "sigflx_lib/sigflx_math_complex_methods.h"
#include "sigflx_lib/sigflx_math_constant.h"
#include <cmath>
#include <limits>

namespace SignumFlux
{
namespace Math
{

template<typename T>
bool isReal(const Complex<T> & object)
{
    if constexpr (std::is_integral_v<T>) {
        return object.imaginary() == T(0);
    } else {
        constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
        return std::abs(object.imaginary()) < epsilon;
    }
}

template<typename T>
bool isImaginary(const Complex<T> & object)
{
    if constexpr (std::is_integral_v<T>) {
        return object.real() == T(0);
    } else {
        constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
        return std::abs(object.real()) < epsilon;
    }
}

template<typename T>
bool isZero(const Complex<T> & object)
{
    T epsilon = std::numeric_limits<T>::epsilon() * 100;
    return object.magnitude() < epsilon;
}

template<typename T>
T abs(const Complex<T> & z)
{
    return z.magnitude();
}

template<typename T>
T norm(const Complex<T> & z)
{
    T mag = z.magnitude();
    return mag * mag;
}

template<typename T>
Complex<T> polar(T radius,T theta)
{
    return Complex(radius * std::cos(theta),radius * std::sin(theta));
}

template<typename T>
Complex<T> exp(const Complex<T> & z)
{
    return polar(std::exp(z.real()),z.imaginary());
}

template<typename T>
Complex<T> ln(const Complex<T> & z)
{
    return Complex(std::log(z.magnitude()),z.argument());
}

template<typename T>
Complex<T> log2(const Complex<T> & z)
{
    return ln(z) / std::log(T(2));
}

template<typename T>
Complex<T> log10(const Complex<T> & z)
{
    return ln(z) / std::log(T(10));
}

template<typename T>
Complex<T> pow(const Complex<T> & z,T n)
{
    T r = z.magnitude();
    T arg = z.argument();
    T rn = std::pow(r,n);
    return Complex(rn * std::cos(n * arg),rn * std::sin(n * arg));
}

template<typename T>
Complex<T> sqrt(const Complex<T> & z)
{
    T r = z.magnitude();
    T arg = z.argument();
    T sqrtr = std::sqrt(r);
    return Complex(sqrtr * std::cos(T(0.5) * arg),sqrtr * std::sin(T(0.5) * arg));
}

template<typename T>
Complex<T> sin(const Complex<T> & z)
{
    return Complex(std::sin(z.real()) * std::cosh(z.imaginary()),std::cos(z.real()) * std::sinh(z.imaginary()));
}

template<typename T>
Complex<T> cos(const Complex<T> & z)
{
    return Complex(std::cos(z.real()) * std::cosh(z.imaginary()),-std::sin(z.real()) * std::sinh(z.imaginary()));
}

template<typename T>
Complex<T> tan(const Complex<T> & z)
{
    return sin(z)/cos(z);
}

template<typename T>
Complex<T> cot(const Complex<T> & z)
{
    return cos(z)/sin(z);
}

template<typename T>
Complex<T> sec(const Complex<T> & z)
{
    return Complex(T(1),T(0))/cos(z);
}

template<typename T>
Complex<T> csc(const Complex<T> & z)
{
    return Complex(T(1),T(0))/sin(z);
}

template<typename T>
Complex<T> asin(const Complex<T> & z)
{
    Complex<T> square = z * z;
    Complex<T> sqrtOneMinusZSquare = sqrt(Complex(T(1),T(0)) - square);
    Complex<T> iz = Complex(T(0),T(1)) * z;
    Complex<T> result = Complex(T(0),T(1)) * ln(sqrtOneMinusZSquare - iz);
    return result;
}

template<typename T>
Complex<T> acos(const Complex<T> & z)
{
    return Complex(pi_v<T>/T(2),T(0)) - asin(z);
}

template<typename T>
Complex<T> atan(const Complex<T> & z)
{
    Complex<T> iz = Complex(T(0),T(1)) * z;
    Complex<T> oneMinuesIZ = Complex(T(1),T(0)) - iz;
    Complex<T> onePlusIZ = Complex(T(1),T(0)) + iz;
    return Complex(T(0),T(-0.5)) * ln(onePlusIZ/oneMinuesIZ);
}

template<typename T>
Complex<T> sinh(const Complex<T> & z)
{
    return Complex(std::sinh(z.real()) * std::cos(z.imaginary()),std::cosh(z.real()) * std::sin(z.imaginary()));
}

template<typename T>
Complex<T> cosh(const Complex<T> & z)
{
    return Complex(std::cosh(z.real()) * std::cos(z.imaginary()),std::sinh(z.real()) * std::sin(z.imaginary()));
}

template<typename T>
Complex<T> tanh(const Complex<T> & z)
{
    return sinh(z)/cosh(z);
}

}
}