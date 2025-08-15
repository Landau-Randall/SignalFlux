#include "sigflx_lib/sigflx_math_constant.h"
#include <iostream>

int main()
{
    std::cout << "int pi is " << SignalFlux::Math::pi_v<int> << '\n'
              << "double pi is " << SignalFlux::Math::pi << '\n'
              << "int e is " << SignalFlux::Math::e_v<int> << '\n' 
              << "double e is " << SignalFlux::Math::e << '\n';    
    return 0;
}
