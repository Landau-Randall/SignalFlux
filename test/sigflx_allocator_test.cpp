#include "sigflx_lib/sigflx_allocator.h"
#include <iostream>

int main()
{
    SignalFlux::AlignedAllocator<int> test;
    int * a = test.allocate(3);
    if (a == nullptr)
    {
        std::cout << "it is null!" << std::endl;
    }
    else
    {
        std::cout << "it is no_null" << std::endl;
    }

    a[0] = 0;
    a[1] = 2;
    std::cout << a[0] << ' '<< a[1] << std::endl;
    std::cout << a << '\n' << a+1 << std::endl;
    test.deallocate(a,3);
    return 0;
}