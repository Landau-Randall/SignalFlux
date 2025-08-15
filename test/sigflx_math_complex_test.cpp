#include "sigflx_lib/sigflx_math_complex.h"
#include "sigflx_lib/sigflx_math_constant.h"
#include <iostream>

int main()
{
    SignalFlux::Math::Complex<double> a(3.0,4.0);
    SignalFlux::Math::Complex<double> b(1.0,0.0);
    std::cout << "is b real?" << SignalFlux::Math::isReal(b) << std::endl;
    std::cout << "is b imaginary?" << SignalFlux::Math::isImaginary(b) << std::endl;
    std::cout << "abs of a is " << SignalFlux::Math::abs(a) << std::endl;
    std::cout << "norm of a is " << SignalFlux::Math::norm(a) << std::endl;
    std::cout << "polar of r 2.0 and theta pi/4 is " << SignalFlux::Math::polar<double>(2.0,SignalFlux::Math::pi/4.0) << std::endl;
    std::cout << "exp of a is " << SignalFlux::Math::exp(a) << std::endl;
    std::cout << "ln of a is " << SignalFlux::Math::ln(a) << std::endl;
    std::cout << "log2 of a is " << SignalFlux::Math::log2(a) << std::endl;
    std::cout << "log10 of a is " << SignalFlux::Math::log10(a) << std::endl;
    std::cout << "pow of a is " << SignalFlux::Math::pow(a,3.0) << std::endl;
    std::cout << "sqrt of a is " << SignalFlux::Math::sqrt(a) << std::endl;

    // 测试三角函数
    std::cout << "sin of a is " << SignalFlux::Math::sin(a) << std::endl;
    std::cout << "cos of a is " << SignalFlux::Math::cos(a) << std::endl;
    std::cout << "tan of a is " << SignalFlux::Math::tan(a) << std::endl;
    std::cout << "sec of a is " << SignalFlux::Math::sec(a) << std::endl;
    std::cout << "csc of a is " << SignalFlux::Math::csc(a) << std::endl;

    // 测试反三角函数
    std::cout << "asin of b is " << SignalFlux::Math::asin(a) << std::endl;
    std::cout << "acos of b is " << SignalFlux::Math::acos(a) << std::endl;
    std::cout << "atan of a is " << SignalFlux::Math::atan(a) << std::endl;

    // 测试双曲函数
    std::cout << "sinh of a is " << SignalFlux::Math::sinh(a) << std::endl;
    std::cout << "cosh of a is " << SignalFlux::Math::cosh(a) << std::endl;
    std::cout << "tanh of a is " << SignalFlux::Math::tanh(a) << std::endl;
    return 0;
}