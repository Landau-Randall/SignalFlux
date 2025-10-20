#pragma once

namespace SignumFlux
{
namespace Platform
{
enum class OSType
{
    Unknown,
    Windows,
    Linux
};

enum class SIMDType
{
    NONE,
    SSE2
};

enum class CompilerType
{
    NONE,
    GCC
};

constexpr OSType detectOS()
{
    #if defined(_WIN32) || defined(_WIN64)
    return OSType::Windows;
    #elif defined(__linux__)
    return OSType::Linux;
    #endif
}

constexpr SIMDType getHighestSIMD()
{
    #if defined(__SSE2__)      
        return SIMDType::SSE2;
    #else
        return SIMDType::NONE;  
    #endif
}

constexpr CompilerType detectCompiler()
{
    #if defined(__GNUC__)
        return CompilerType::GCC;
    #else
        return CompilerType::NONE;
    #endif
}


constexpr OSType CurrentOS = detectOS();
constexpr SIMDType CurrentSIMD = getHighestSIMD();
constexpr CompilerType CurrentCompiler = detectCompiler();

}
} 
