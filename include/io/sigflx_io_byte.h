#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>

namespace SignumFlux
{
namespace IO
{
enum class Endian
{
    Little,
    Big
};

template<typename T>
T bytesRead(const std::uint8_t * buffer,Endian endianType);

template<typename T>
void bytesWrite(std::uint8_t * buffer,T value,Endian endianType);

}
}

#include "../../src/io/sigflx_io_byte.tpp"