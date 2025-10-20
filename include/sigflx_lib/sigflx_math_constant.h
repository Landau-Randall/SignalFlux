#pragma once

namespace SignumFlux
{
namespace Math
{
template<typename T>
constexpr T pi_v = static_cast<T>(3.14159265358979323846);

template<typename T>
constexpr T e_v = static_cast<T>(2.71828182845904523536);

template<typename T>
constexpr T phi_v = static_cast<T>(1.61803398874989484820);

template<typename T>
constexpr T sqrt2_v = static_cast<T>(1.41421356237309504880);

template<typename T>
constexpr T ln2_v = static_cast<T>(0.69314718055994530942);

template<typename T>
constexpr T ln10_v = static_cast<T>(2.30258509299404568402);

constexpr double pi = pi_v<double>;
constexpr double e  = e_v<double>;
constexpr double phi= phi_v<double>;
constexpr double sqrt2 = sqrt2_v<double>;
constexpr double ln2   = ln2_v<double>;
constexpr double ln10  = ln10_v<double>;

}
}