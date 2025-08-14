#pragma once

namespace SignalFlux
{
enum class OSType
{
    Unknown,
    Windows,
    Linux
};

constexpr OSType detectOS()
{
    #if defined(_WIN32) || defined(_WIN64)
    return OSType::Windows;
    #elif defined(__linux__)
    return OSType::Linux;
    #endif
};

constexpr OSType CurrentOS = detectOS();

} 
