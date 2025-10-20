#include "sigflx_lib/sigflx_allocators_buffer_pool.h"

namespace SignumFlux
{
namespace Allocators
{
template<typename T,std::size_t BufferCount,std::size_t BufferSize>
typename BufferPool<T,BufferCount,BufferSize>::Node * BufferPool<T,BufferCount,BufferSize>::lastNode(Node * entrance_)
{   
    if (!entrance_)
        return nullptr;

    while (entrance_->next != nullptr)
    {
        entrance_ = entrance_->next;
    }
    return entrance_;
}

template<typename T,std::size_t BufferCount,std::size_t BufferSize>
BufferPool<T,BufferCount,BufferSize>::BufferPool()
{
    void * ptr = Platform::Allocate<Platform::CurrentOS>::allocate(BufferCount * BufferSize * sizeof(T),64);
    if (ptr != nullptr)
    {
        data_ = static_cast<Pointer>(ptr);
    }
    auto & fixedPoll = FixedBlockPool::instance();
    freeList_ = fixedPoll.allocate<Node>(1);
    freeList_->buffer = data_;

    Node* prev = freeList_;
    for (SizeType i = 1; i < BufferCount; ++i) {
        Node* node = fixedPoll.allocate<Node>(1);
        node->buffer = data_ + i * BufferSize;
        prev->next = node;
        prev = node;
    }
    prev->next = nullptr;
}

template<typename T,std::size_t BufferCount,std::size_t BufferSize>
BufferPool<T,BufferCount,BufferSize>::~BufferPool()
{
    if (data_ != nullptr)
    {
        Platform::DeAllocator<Platform::CurrentOS>::deallocate(data_);
        data_ = nullptr;
    }

    auto & fixedPoll = FixedBlockPool::instance();
    Node * entrance = freeList_;
    while (entrance != nullptr)
    {
        Node * next = entrance->next;
        fixedPoll.deallocate<Node>(entrance,1);
        entrance = next;
    }
    freeList_ = nullptr;
}

template<typename T,std::size_t BufferCount,std::size_t BufferSize>
typename BufferPool<T,BufferCount,BufferSize>::Pointer BufferPool<T,BufferCount,BufferSize>::allocate(SizeType n)
{
    assert(n == BufferSize);

    auto & fixedPoll = FixedBlockPool::instance();
    if (freeList_ != nullptr)
    {
        Pointer block = freeList_->buffer;
        Node * next = freeList_->next;
        fixedPoll.deallocate<Node>(freeList_,1);
        freeList_ = next;
        return block;
    }
    else
    {
        return nullptr;
    }
}

template<typename T,std::size_t BufferCount,std::size_t BufferSize>
void BufferPool<T,BufferCount,BufferSize>::deallocate(Pointer ptr,SizeType n)
{
    assert(n == BufferSize);

    auto & fixedPoll = FixedBlockPool::instance();
    Node * node = fixedPoll.allocate<Node>(1);
    node->buffer = ptr;
    node->next = freeList_;
    freeList_ = node;
    node = nullptr;
}

template<typename T,std::size_t BufferCount,std::size_t BufferSize>
BufferPoolAllocator<T,BufferCount,BufferSize>::BufferPoolAllocator(BufferPool<T,BufferCount,BufferSize> & pool):
pool_(&pool)
{
    
}
template<typename T,std::size_t BufferCount,std::size_t BufferSize>
typename BufferPoolAllocator<T,BufferCount,BufferSize>::Pointer BufferPoolAllocator<T,BufferCount,BufferSize>::allocate(SizeType n)
{
    if (n == 0)
    {
        return nullptr;
    }
    return pool_->allocate(n);
}

template<typename T,std::size_t BufferCount,std::size_t BufferSize>
void BufferPoolAllocator<T,BufferCount,BufferSize>::deallocate(Pointer ptr,SizeType n)
{
    pool_->deallocate(ptr,n);
}

}
}