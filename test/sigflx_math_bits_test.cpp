#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_math_bits.h"

using namespace SignumFlux::Math;

TEST(BitsMethodTest,AllTest)
{
    std::uint16_t a = 0x1010;
    std::uint16_t b = setBit(a,0);
    std::uint16_t c = clearBit(a,4);
    std::uint16_t d = toggleBit(a,12);
    bool e = checkBit(a,4);
    EXPECT_EQ(b,0x1011);
    EXPECT_EQ(c,0x1000);
    EXPECT_EQ(d,0x0010);
    EXPECT_TRUE(e);
}

TEST(BitsMethodTest,ExtraTest)
{
    std::uint16_t a = 0x1010;
    std::uint16_t b = flipbits(a);
    std::uint16_t c = extractRange(a,4,4);
    std::uint16_t d = 0x1100;
    std::uint16_t e = setRange(d,0,8);
    std::uint16_t f = generateMask<std::uint16_t>(8,8);
    std::uint16_t g = applyMask(a,f);
    EXPECT_EQ(b,0xEFEF);
    EXPECT_EQ(c,0x01);
    EXPECT_EQ(e,0x11FF);
    EXPECT_EQ(f,0xFF00);
    EXPECT_EQ(g,0x1000);
}