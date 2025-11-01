#pragma once
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace SignumFlux
{
namespace Math
{
template<typename T>
inline T setBit(T value,std::size_t bit);

template<typename T>
inline T clearBit(T value,std::size_t bit);

template<typename T>
inline T toggleBit(T value,std::size_t bit);

template<typename T>
inline bool checkBit(T value,std::size_t bit);

template<typename T>
inline T flipbits(T value);

template<typename T>
inline T extractRange(T value,std::size_t start,std::size_t length);

template<typename T>
inline T setRange(T value,std::size_t start, std::size_t length);

template<typename T>
inline T generateMask(std::size_t start,std::size_t length);

template<typename T>
inline T applyMask(T value,T mask);
}
}

#include "../../src/sigflx_lib/sigflx_math_bits.tpp"