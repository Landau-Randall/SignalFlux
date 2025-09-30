#include "sigflx_lib/sigflx_container_array.h"


namespace SignalFlux
{
namespace Container
{
template<typename T,std::size_t N>
constexpr Array<T,N>::Array(std::initializer_list<T> list)
{
    SizeType i = 0;
    for (const auto & ele : list)
    {
        if (i >= N)
            break;
        data_[i++] = ele;
    }

    for (;i < N ;++i)
    {
        data_[i] = T{};
    }
}

template<typename T,std::size_t N>
constexpr Array<T,N> & Array<T,N>::operator=(std::initializer_list<T> list)
{
    SizeType i = 0;
    for (const auto & ele : list)
    {
        if (i >= N)
            break;
        data_[i++] = ele;
    }

    for (;i < N ;++i)
    {
        data_[i] = T{};
    }
    return *this;
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::Reference Array<T,N>::operator[](SizeType offset)
{
    return data_[offset];
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::ConstReference Array<T,N>::operator[](SizeType offset) const
{
    return data_[offset];
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::Reference Array<T,N>::at(SizeType offset)
{
    if (offset >= N)
        throw std::out_of_range("offset out of range!");
    return data_[offset];
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::ConstReference Array<T,N>::at(SizeType offset) const
{
    if (offset >= N)
        throw std::out_of_range("offset out of range!");
    return data_[offset];
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::Reference Array<T,N>::front()
{
    assert(N > 0 && "Array is empty!");
    return data_[0];
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::ConstReference Array<T,N>::front() const
{
    assert(N > 0 && "Array is empty!");
    return data_[0];
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::Reference Array<T,N>::back()
{
    assert(N > 0 && "Array is empty!");
    return data_[N-1];
}

template<typename T,std::size_t N>
constexpr typename Array<T,N>::ConstReference Array<T,N>::back() const
{
    assert(N > 0 && "Array is empty!");
    return data_[N-1];
}

template<typename T,std::size_t N>
constexpr void Array<T,N>::fill(ConstReference value)
{
    if constexpr (N != 0)
    {
        std::fill(data_,data_ + N,value);
    }
}

template<typename T,std::size_t N>
constexpr void Array<T,N>::swap(Array & object) noexcept
{
    for (SizeType i = 0; i < N; ++i) 
    {
        std::swap(data_[i], object.data_[i]);
    }
}

}
}