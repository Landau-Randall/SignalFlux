#pragma once
#include "sigflx_platform_detect.h"
#include <cstddef>
#include <exception>
#include <stdlib.h>

namespace SignumFlux
{
namespace Platform
{
template<OSType > 
struct Allocate;

template<> 
struct Allocate<OSType::Unknown> 
{ 
    static void * allocate(std::size_t n,std::size_t alignSize) 
    { 
        throw std::bad_alloc();
    }
};

template<> 
struct Allocate<OSType::Linux>
{ 
    static void * allocate(std::size_t n,std::size_t alignSize) 
    {
        void * pointer = nullptr;
        int code = posix_memalign(&pointer,alignSize,n);
        if (code == 0)
        {
            return pointer;
        }
        else
        {
            return nullptr;
        }
    }
};

template<OSType >
struct DeAllocator;

template<>
struct DeAllocator<OSType::Unknown>
{
    static void deallocate(void * pointer)
    {
        throw std::bad_alloc();
    }
};

template<>
struct DeAllocator<OSType::Linux>
{
    static void deallocate(void * pointer)
    {
        free(pointer);
    }
};
}
}