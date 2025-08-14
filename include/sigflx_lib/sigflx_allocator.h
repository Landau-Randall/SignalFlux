#pragma once

#include <cstddef>

namespace SignalFlux
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
    void deallocate(Pointer ptr);
};
}