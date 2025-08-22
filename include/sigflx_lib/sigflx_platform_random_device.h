#pragma once
#include <stdexcept>
#include <cstdio>
#include "sigflx_lib/sigflx_platform_detect.h"


namespace SignalFlux
{
namespace Platform
{
template<OSType > 
struct RandomDevice;

template<>
struct RandomDevice<OSType::Unknown>
{
    template<typename UnsignedIntType>
    static UnsignedIntType getRandomNumber() 
    {
        throw std::runtime_error("system type unknown!\n");
    }
};

template<>
struct RandomDevice<OSType::Linux>
{
    template<typename UnsignedIntType>
    static UnsignedIntType getRandomNumber()
    {
        FILE * deviceFile = std::fopen("/dev/urandom","r");
        UnsignedIntType result = UnsignedIntType(0);
        std::fread(&result,sizeof(result),1,deviceFile);
        std::fclose(deviceFile);
        return result;
    }
};

}
}