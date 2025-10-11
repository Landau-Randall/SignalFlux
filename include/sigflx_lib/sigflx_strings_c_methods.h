#pragma once
#include <cstddef>


namespace SignalFlux
{
namespace Strings
{
template<typename CharType>
std::size_t stringLength(const CharType * str);

template<typename CharType>
void stringCopy(CharType * target,const CharType * source,std::size_t n);

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr);

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr,std::size_t n);

template<typename CharType>
const CharType* stringFind(const CharType* str, CharType ch);

template<typename CharType> 
const CharType* stringFind(const CharType* str, const CharType* substr);

template<typename CharType> 
void stringFill(CharType* dest, CharType value, std::size_t n);

}
}

#include "../../src/sigflx_lib/sigflx_strings_c_methods.tpp"