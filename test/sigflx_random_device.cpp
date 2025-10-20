#include <gtest/gtest.h>
#include <cstdint>
#include "sigflx_lib/sigflx_platform_random_device.h"
#include "sigflx_lib/sigflx_random_device.h"


TEST(PlatformRandomDeivce,PlatformRandomMethod)
{
    EXPECT_THROW(SignumFlux::Platform::RandomDevice<SignumFlux::Platform::OSType::Unknown>::getRandomNumber<std::uint32_t>(),std::runtime_error);
    EXPECT_NO_THROW(SignumFlux::Platform::RandomDevice<SignumFlux::Platform::OSType::Linux>::getRandomNumber<std::uint32_t>());
}

TEST(RandomDeviceUtils,RandomDeviceMethod)
{
    SignumFlux::Random::RandomDevice<std::uint32_t> rd;
    EXPECT_NO_THROW(rd());
    EXPECT_EQ(rd.min(),0);
    EXPECT_EQ(rd.max(),((1ULL<<32) - 1));
}