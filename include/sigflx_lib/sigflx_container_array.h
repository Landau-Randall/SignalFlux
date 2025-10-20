#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

namespace SignumFlux
{
namespace Container
{
template<typename T,std::size_t N>
class Array
{
public:
    using ValueType = T;
    using SizeType  = std::size_t;
    using Reference = T &;
    using ConstReference = const T &;
    using Pointer = T *;
    using ConstPointer = const T *;
private:
    ValueType data_[N];
public:
    constexpr Array() = default;
    constexpr Array(const Array & object) = default;
    constexpr Array(Array && object) = default;
    constexpr Array(std::initializer_list<T> list);

    ~Array() = default;

    constexpr Array & operator=(const Array & object) = default;
    constexpr Array & operator=(Array && object) = default;
    constexpr Array & operator=(std::initializer_list<T> list);

    constexpr Reference operator[](SizeType offset);
    constexpr ConstReference operator[](SizeType offset) const;
    constexpr Reference at(SizeType offset);
    constexpr ConstReference at(SizeType offset) const;
    constexpr Reference front();
    constexpr ConstReference front() const;
    constexpr Reference back();
    constexpr ConstReference back() const;

    constexpr Pointer data() noexcept { return (N != 0) ? (data_) : (nullptr); };
    constexpr bool empty() const noexcept { return N == 0; };
    constexpr ConstPointer data() const noexcept { return (N != 0) ? (data_) : (nullptr); };
    constexpr SizeType size() const noexcept { return N; };

    constexpr void fill(ConstReference value);
    constexpr void swap(Array & object) noexcept;
};
}
}

#include "../../src/sigflx_lib/sigflx_container_array.tpp"