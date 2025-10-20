#pragma once
#include <type_traits>
#include <initializer_list>
#include <iostream>

namespace SignumFlux
{
namespace Math
{
template<typename T>
class Complex
{
    static_assert(std::is_arithmetic<T>::value,"T must be arithmetic value!");
private:
    T real_;
    T imaginary_;
public:
    Complex():real_(T()),imaginary_(T()) {};
    Complex(T realValue,T imaginaryValue):real_(realValue),imaginary_(imaginaryValue) {};
    Complex(const Complex & object) = default;
    Complex(Complex && object) = default;
    Complex(std::initializer_list<T> list);

    bool operator==(const Complex & object);
    bool operator!=(const Complex & object);

    Complex & operator=(const Complex & object) = default;
    Complex & operator=(Complex && object) = default;
    Complex & operator=(std::initializer_list<T> list);

    const T & real() const;
    T & real();
    const T & imaginary() const;
    T & imaginary();

    Complex comjugate() const;
    Complex operator+(const Complex & object) const;
    Complex operator+(T scalar) const;
    Complex operator-(const Complex & object) const;
    Complex operator-(T scalar) const;
    Complex operator*(const Complex & object) const;
    Complex operator*(T scalar) const;
    Complex operator/(const Complex & object) const;
    Complex operator/(T scalar) const;

    T magnitude() const;
    T argument() const;

    friend std::ostream & operator<<(std::ostream & os,const Complex & object)
    {
        os << object.real_ ;
        if (object.imaginary_ >= 0)
            os << '+';
        os << object.imaginary_ << "i";
        return os;
    }
    friend std::istream & operator>>(std::istream & is,Complex & object)
    {
        is >> object.real_ >> object.imaginary_;
        return is;
    }

};
}
}

#include "../../src/sigflx_lib/sigflx_math_complex.tpp"