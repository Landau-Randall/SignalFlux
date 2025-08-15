#include "sigflx_lib/sigflx_complex.h"

int main()
{
    SignalFlux::Math::Complex<double> a(1.0,1.0);
    SignalFlux::Math::Complex<double> b(3.0,4.0);
    std::cout << "a real part " << a.real() << ' ' << "a imaginary part " << a.imaginary() << std::endl;
    std::cout << "b real part " << b.real() << ' ' << "b imaginary part " << b.imaginary() << std::endl;
    std::cout << "a is " << a << ' ' << "b is " << b << std::endl;
    std::cout << "a conjugate is " << a.comjugate() << ' ' << "b conjugate is " << b.comjugate() << std::endl;
    std::cout << "a + b is " << a + b << std::endl;
    std::cout << "a - b is " << a - b << std::endl;
    std::cout << "a * b is " << a * b << std::endl;
    std::cout << "a / b is " << a / b << std::endl;
    std::cout << "a magnitude is " << a.magnitude() << ' ' << "b magnitude is " << b.magnitude() << std::endl;
    std::cout << "a argument  is " << a.argument() << ' ' << "b argument is " << b.argument() << std::endl;
    std::cout << "input two real number :";
    std::cin >> a;
    std::cout << std::endl << "now a is " << a << std::endl;
    return 0;
}