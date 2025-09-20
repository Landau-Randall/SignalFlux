#pragma once
#include <type_traits>

namespace SignalFlux
{
namespace Random
{
template<typename UnsignedIntType>
class BaseEngine
{
protected:
    static_assert(std::is_unsigned_v<UnsignedIntType>,"Engine result type must be unsigned integer");
public:
    using ResultType = UnsignedIntType;

    virtual ResultType operator()() = 0;
    virtual void seed(ResultType value) = 0;
    virtual void discard(unsigned long long step) = 0;
    virtual const char * name() const noexcept = 0;

    virtual ~BaseEngine() = default;
};
}
}