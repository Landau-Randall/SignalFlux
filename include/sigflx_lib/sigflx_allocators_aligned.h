#pragma once

#include <cstddef>
#include "sigflx_lib/sigflx_platform_allocator.h"

namespace SignalFlux
{
namespace Allocators
{
template<typename T,std::size_t AlignSize = 64UL>
class AlignedAllocator
{
public:
    using ValueType = T;
    using Pointer = T*;
    using SizeType = std::size_t;
public:
    AlignedAllocator() noexcept = default;
    Pointer allocate(SizeType n);
    void deallocate(Pointer ptr,std::size_t n);
};
}
}

#include "../../src/sigflx_lib/sigflx_allocators_aligned.tpp"