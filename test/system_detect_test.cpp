#include "sigflx_lib/system_detect.h"
#include <iostream>

int main()
{
    if (SignalFlux::CurrentOS == SignalFlux::OSType::Linux)
    {
        std::cout << "it is linux!" << std::endl;
    }
    return 0;
}