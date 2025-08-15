#include "sigflx_lib/sigflx_complex.h"
#include "sigflx_lib/sigflx_math_constant.h"
#include <iostream>
#include <cmath>

namespace SignalFlux
{
namespace Math
{
template<typename T>
Complex<T>::Complex(std::initializer_list<T> list)
{
    if (list.size() == 2)
    {
        real_ = *list.begin();
        imaginary_ = *list.end();
    }
    else
    {
        std::cout << "list size error!\n";
    }
}

template<typename T>
bool Complex<T>::operator==(const Complex & object)
{
    return real_ == object.real_ && imaginary_ == object.imaginary_;
}

template<typename T>
bool Complex<T>::operator!=(const Complex & object)
{
    return !(*this == object);
}

template<typename T>
Complex<T> & Complex<T>::operator=(std::initializer_list<T> list)
{
    if (list.size() == 2)
    {
        real_ = *list.begin();
        imaginary_ = *list.end();
    }
    else
    {
        std::cout << "list size error\n";
    }
}

template<typename T>
const T & Complex<T>::real() const
{
    return real_;
}

template<typename T>
T & Complex<T>::real()
{
    return real_;
}

template<typename T>
const T & Complex<T>::imaginary() const
{
    return imaginary_;
}

template<typename T>
T & Complex<T>::imaginary()
{
    return imaginary_;
}

template<typename T>
Complex<T> Complex<T>::comjugate() const
{
    return Complex(real_,-imaginary_);
}

template<typename T>
Complex<T> Complex<T>::operator+(const Complex<T> & object)
{
    return Complex(this->real_ + object.real_,this->imaginary_+object.imaginary_);
}

template<typename T>
Complex<T> Complex<T>::operator+(T scalar)
{
    return Complex(this->real_ + scalar,this->imaginary_);
}

template<typename T>
Complex<T> Complex<T>::operator-(const Complex<T> & object)
{
    return Complex(this->real_ - object.real_,this->imaginary_-object.imaginary_);
}

template<typename T>
Complex<T> Complex<T>::operator-(T scalar)
{
    return Complex(this->real_ - scalar,this->imaginary_);
}

template<typename T>
Complex<T> Complex<T>::operator*(const Complex<T> & object)
{
    return Complex(this->real_ * object.real_ - this->imaginary_ * object.imaginary_,this->real_ * object.imaginary_ + this->imaginary_ * object.real_);
}

template<typename T>
Complex<T> Complex<T>::operator*(T scalar)
{
    return Complex(this->real_ * scalar,this->imaginary_ * scalar);
}

template<typename T>
Complex<T> Complex<T>::operator/(const Complex<T> & object)
{
    Complex<T> conjugateObject = object.comjugate();
    T norm = object.magnitude();
    T square = norm * norm;
    Complex<T> result = *this * conjugateObject;
    return Complex(result.real_/square,result.imaginary_/square);
}

template<typename T>
Complex<T> Complex<T>::operator/(T scalar)
{
    return Complex(this->real_ / scalar,this->imaginary_ / scalar);
}

template<typename T>
T Complex<T>::magnitude() const
{
    return std::sqrt(real_ * real_ + imaginary_ * imaginary_);
}

template<typename T>
T Complex<T>::argument() const
{
    if (imaginary_ != 0)
    {
        return 2.0 * std::atan2(imaginary_ , (this->magnitude() + real_));
    }
    else
    {
       return real_ > 0 ? (T(0)) : (pi_v<T>);
    }
}

}
}