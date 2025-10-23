#include "io/sigflx_io_byte.h"

namespace SignumFlux
{
namespace IO
{
template<typename T>
T bytesRead(const std::uint8_t * buffer,Endian endianType)
{
    constexpr std::size_t width = sizeof(T);
    if constexpr (width == 1)
    {
        return *buffer;
    }
    else
    {
        std::size_t sign = static_cast<std::size_t>(endianType);
        std::uint8_t temp[width];
        T value;
        for (std::size_t i = 0;i < width;++i)
        {
            temp[i] = buffer[(1 - sign) * i + (sign) * (width - 1 - i)];
        }
        std::memcpy(&value,temp,width);
        return value;
    }
}

template<typename T>
void bytesWrite(std::uint8_t * buffer,T value,Endian endianType)
{
    constexpr std::size_t width = sizeof(T);
    if constexpr (width == 1)
    {
        *buffer = static_cast<std::uint8_t>(value);
    }
    else
    {
        std::size_t sign = static_cast<std::size_t>(endianType);
        std::uint8_t temp[width];
        std::memcpy(temp,&value,width);
        for (std::size_t i = 0;i < width;++i)
        {
            buffer[i] = temp[(1 - sign) * i + (sign) * (width - 1 - i)];
        }
    }
}
}
}