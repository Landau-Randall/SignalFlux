#pragma once
#include <cstdint>
#include "sigflx_platform_detect.h"

namespace SignumFlux
{
namespace Platform
{
template<CompilerType >
struct CompilerMethods;

template<>
struct CompilerMethods<CompilerType::NONE>
{
    static_assert("Unsupported Compiler Type!");
};

template<>
struct CompilerMethods<CompilerType::GCC>
{
    static int leadingZeros(std::uint8_t x)
    {
        return x ? __builtin_clz(static_cast<std::uint32_t>(x)) - 24 : 8;
    };
    
    static int leadingZeros(std::uint16_t x)
    {
        return x ? __builtin_clz(static_cast<std::uint32_t>(x)) - 16 : 16;
    };

    static int leadingZeros(std::uint32_t x)
    {
        return x ? __builtin_clz(x) : 32;
    };

    static int leadingZeros(std::uint64_t x)
    {
        return x ? __builtin_clzll(x) : 64;
    };

    static int trailingZeros(std::uint8_t x)
    {
        return x ? __builtin_ctz(static_cast<std::uint32_t>(x)) : 8;
    }
    
    static int trailingZeros(std::uint16_t x)
    {
        return x ? __builtin_ctz(static_cast<std::uint32_t>(x)) : 16;
    }
    
    static int trailingZeros(std::uint32_t x)
    {
        return x ? __builtin_ctz(x) : 32;
    }
    
    static int trailingZeros(std::uint64_t x)
    {
        return x ? __builtin_ctzll(x) : 64;
    }

    static int populationCount(std::uint8_t x)
    {
        return __builtin_popcount(static_cast<std::uint32_t>(x));
    }

    static int populationCount(std::uint16_t x)
    {
        return __builtin_popcount(static_cast<std::uint32_t>(x));
    }

    static int populationCount(std::uint32_t x)
    {
        return __builtin_popcount(x);
    }

    static int populationCount(std::uint64_t x)
    {
        return __builtin_popcountll(x);
    }

    static std::uint16_t byteSwap(std::uint16_t x)
    {
        return __builtin_bswap16(x);
    }

    static std::uint32_t byteSwap(std::uint32_t x)
    {
        return __builtin_bswap32(x);
    }

    static std::uint64_t byteSwap(std::uint64_t x)
    {
        return __builtin_bswap64(x);
    }
};

}
}