#include "sigflx_lib/sigflx_strings_c_methods.h"

namespace SignalFlux
{
namespace Strings
{
template<typename CharType>
std::size_t stringLength(const CharType * str)
{
    if (str != nullptr)
    {
        std::size_t index = 0;
        while (str[index] != static_cast<CharType>('\0'))
        {
            index++;
        }
        return index;
    }
    else
    {
        return 0;
    }
}

template<typename CharType>
void stringCopy(CharType * target,const CharType * source,std::size_t n)
{
    if (target != nullptr && source != nullptr)
    {
        std::size_t i = 0;
        for (;i < n - 1 && (source[i] != static_cast<CharType>('\0'));++i)
        {
            target[i] = source[i];
        }
        target[i] = static_cast<CharType>('\0');
    }
    else
    {
        return;
    }
}

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr)
{
    if (firstStr != nullptr && secondStr != nullptr)
    {
        std::size_t i = 0;
        while (firstStr[i] != static_cast<CharType>('\0') && secondStr[i] != static_cast<CharType>('\0'))
        {
            if (firstStr[i] > secondStr[i])
                return 1;
            if (firstStr[i] < secondStr[i])
                return -1;
            ++i;
        }
        if (firstStr[i] == static_cast<CharType>('\0') && secondStr[i] == static_cast<CharType>('\0'))
            return 0;
        if (firstStr[i] == static_cast<CharType>('\0'))
            return -1;
        return 1;
    }
    else
    {
        return -2;
    }
}

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr,std::size_t n)
{
    if (firstStr != nullptr && secondStr != nullptr && n != 0)
    {
        std::size_t i = 0;
        for (;i < n && firstStr[i] != static_cast<CharType>('\0') && secondStr[i] != static_cast<CharType>('\0');++i)
        {
            if (firstStr[i] > secondStr[i])
                return 1;
            if (firstStr[i] < secondStr[i])
                return -1;
        }
        if (i == n)
            return 0;
        if (firstStr[i] == secondStr[i])
            return 0;
        if (firstStr[i] == static_cast<CharType>('\0'))
            return -1;
        return 1;
        
    }
    else
    {
        return -2;
    }
}

template<typename CharType>
const CharType* stringFind(const CharType* str, CharType ch)
{
    if (str != nullptr)
    {
        if (ch == static_cast<CharType>('\0'))
        {
            return nullptr;
        }

        while(*str != static_cast<CharType>('\0'))
        {
            if (*str == ch)
            {
                return str;
            }
            ++str;
        }
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

template<typename CharType> 
const CharType* stringFind(const CharType* str, const CharType* substr)
{
    if (str != nullptr)
    {
        if (substr == nullptr || *substr == static_cast<CharType>('\0'))
            return str;
        
        const CharType * copystr,* copysubstr;
        while (*str != static_cast<CharType>('\0'))
        {
            copystr = str;
            copysubstr = substr;
            while (*copystr == *copysubstr && *copysubstr != static_cast<CharType>('\0'))
            {
                ++copystr;
                ++copysubstr;
            }
            if (*copysubstr == static_cast<CharType>('\0'))
                return str;
            ++str;
        }

        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

template<typename CharType> 
void stringFill(CharType* dest, CharType value, std::size_t n)
{
    if (dest != nullptr)
    {
        for (std::size_t i = 0;i < n;i++)
        {
            dest[i] = value;
        }
    }
    else
    {
        return;
    }
}
}
}