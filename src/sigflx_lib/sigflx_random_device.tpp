#include <limits>
#include "sigflx_lib/sigflx_platform_detect.h"
#include "sigflx_lib/sigflx_platform_random_device.h"
#include "sigflx_lib/sigflx_random_device.h"


namespace SignalFlux
{
namespace Random
{
template<typename UnsignedIntType>
typename RandomDevice<UnsignedIntType>::ResultType RandomDevice<UnsignedIntType>::operator()() const
{
    return Platform::RandomDevice<Platform::CurrentOS>::getRandomNumber<ResultType>();
}

template<typename UnsignedIntType>
typename RandomDevice<UnsignedIntType>::ResultType RandomDevice<UnsignedIntType>::min() noexcept
{
    return std::numeric_limits<ResultType>::min();
}

template<typename UnsignedIntType>
typename RandomDevice<UnsignedIntType>::ResultType RandomDevice<UnsignedIntType>::max() noexcept
{
    return std::numeric_limits<ResultType>::max();
}

}
}