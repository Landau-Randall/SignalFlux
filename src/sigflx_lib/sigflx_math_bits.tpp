#include "sigflx_lib/sigflx_math_bits.h"


namespace SignumFlux
{
namespace Math
{
template<typename T>
inline T setBit(T value,std::size_t bit)
{
    static_assert(std::is_integral<T>::value,"T must be interger type\n");
    return value | (1UL << bit);
}

template<typename T>
inline T clearBit(T value,std::size_t bit)
{
    static_assert(std::is_integral<T>::value,"T must be interger type\n");
    return value & ~(T(1) << bit);
}

template<typename T>
inline T toggleBit(T value, std::size_t bit) 
{
    return value ^ (T(1) << bit);
}

template<typename T>
inline bool checkBit(T value, std::size_t bit) 
{
    return (value & (T(1) << bit)) != 0;
}

template<typename T>
inline T flipbits(T value)
{
    static_assert(std::is_integral<T>::value,"T must be interger type\n");
    return ~value;
}

template<typename T>
inline T extractRange(T value,std::size_t start,std::size_t length)
{
    static_assert(std::is_integral<T>::value,"T must be interger type\n");
    T mask = (T(1) << length) - 1;
    return (value >> start) & mask;
}

template<typename T>
inline T setRange(T value,std::size_t start, std::size_t length)
{
    static_assert(std::is_integral<T>::value, "T must be an integer type\n");
    T mask = ((T(1) << length) - 1) << start; 
    return value | mask; 
}

template<typename T>
inline T generateMask(std::size_t start,std::size_t length)
{
    return ((T(1) << length) - 1) << start;
}

template<typename T>
inline T applyMask(T value,T mask)
{
    static_assert(std::is_integral<T>::value, "T must be an integer type\n");
    return value & mask;
}
}
}
