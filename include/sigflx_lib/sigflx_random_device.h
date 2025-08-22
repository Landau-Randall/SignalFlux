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
    static ResultType min() noexcept;
    static ResultType max() noexcept;
};
}
}

#include "../../src/sigflx_lib/sigflx_random_device.tpp"