#include "sigflx_lib/sigflx_allocators_aligned.h"


namespace SignalFlux
{
namespace Allocators
{
template<typename T,std::size_t AlignSize>
typename AlignedAllocator<T,AlignSize>::Pointer AlignedAllocator<T,AlignSize>::allocate(SizeType n)
{
    if (n == 0)
    {
        return nullptr;
    }

    void * result = Platform::Allocate<Platform::CurrentOS>::allocate(n * sizeof(T),AlignSize);
    if (result != nullptr)
    {
        return static_cast<T*>(result);
    }
    else
    {
        return nullptr;
    }
}

template<typename T,std::size_t AlignSize>
void AlignedAllocator<T,AlignSize>::deallocate(Pointer ptr,std::size_t n)
{
    Platform::DeAllocator<Platform::CurrentOS>::deallocate(ptr);
}
}
}