#pragma once

namespace SignalFlux
{
namespace Random
{
template<typename UnsignedIntType>
class RandomDevice
{
public:
    using ResultType = UnsignedIntType;
public:
    RandomDevice() = default;
    RandomDevice(const RandomDevice & object) = delete;

    ResultType operator()() const;
    static constexpr ResultType min();
    static constexpr ResultType max();
};
}
}

#include "../../src/sigflx_lib/sigflx_random_device.tpp"