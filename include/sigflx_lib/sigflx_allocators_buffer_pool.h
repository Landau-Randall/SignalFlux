#pragma once
#include <cstddef>
#include "sigflx_lib/sigflx_allocators_fixed_pool.h"


namespace SignumFlux
{
namespace Allocators
{
template<typename T,std::size_t BufferCount,std::size_t BufferSize>
class BufferPool
{
public:
    using ValueType = T;
    using Pointer = T *;
    using SizeType = std::size_t;
    struct Node 
    {
        Pointer buffer = nullptr;
        Node * next = nullptr;
    };
private:
    Pointer data_ = nullptr;
    Node * freeList_ = nullptr;
    Node * lastNode(Node * entrance);
public:
    BufferPool();
    BufferPool(const BufferPool & object) = delete;
    BufferPool(BufferPool && object) = delete;

    ~BufferPool();

    BufferPool & operator=(const BufferPool & object) = delete;
    BufferPool & operator=(BufferPool && object) = delete;

    Pointer allocate(SizeType n);

    void deallocate(Pointer ptr,SizeType n);
};

template<typename T,std::size_t BufferCount,std::size_t BufferSize>
class BufferPoolAllocator
{
public:
    using ValueType = T;
    using Pointer = T *;
    using SizeType = std::size_t;
private:
    BufferPool<T,BufferCount,BufferSize> * pool_ = nullptr;
public:
    BufferPoolAllocator(BufferPool<T,BufferCount,BufferSize> & pool);
    Pointer allocate(SizeType n);
    void deallocate(Pointer ptr,SizeType n);
};
}
}

#include "../../src/sigflx_lib/sigflx_allocators_buffer_pool.tpp"