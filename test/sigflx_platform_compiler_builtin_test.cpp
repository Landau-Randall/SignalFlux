#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_platform_compiler_bulitin.h"



TEST(GCCBuiltinMethods,LeadingZeros)
{
    using namespace SignalFlux::Platform;
    std::uint8_t a = 0x31;//0011 0001
    std::uint8_t a_z = 0x00;
    std::uint16_t b = 0x0132;//0000 0001 0011 0010
    std::uint16_t b_z = 0x0000;
    std::uint32_t c = 0x01000000;// 0000 0001
    std::uint32_t c_z = 0x00000000;
    std::uint64_t d = 0x0001000000000000;//0000 0000 0000 0001
    std::uint64_t d_z = 0x0000000000000000;
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(a),2);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(a_z),8);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(b),7);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(b_z),16);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(c),7);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(c_z),32);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(d),15);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::leadingZeros(d_z),64);
}

TEST(GCCBuiltinMethods,TrailingZeros)
{
    using namespace SignalFlux::Platform;
    std::uint8_t a = 0x38;//0011 1000
    std::uint8_t a_z = 0x00;
    std::uint16_t b = 0x0132;//0000 0001 0011 0010
    std::uint16_t b_z = 0x0000;
    std::uint32_t c = 0x01000100;// 0001 0000 0000
    std::uint32_t c_z = 0x00000000;
    std::uint64_t d = 0x0000000000040000;//0100 0000 0000 0000 0000
    std::uint64_t d_z = 0x0000000000000000;
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(a),3);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(a_z),8);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(b),1);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(b_z),16);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(c),8);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(c_z),32);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(d),18);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::trailingZeros(d_z),64);
}

TEST(GCCBulitinMethods,PopulationCount)
{
    using namespace SignalFlux::Platform;
    std::uint8_t a = 0x38;//0011 1000
    std::uint8_t a_z = 0x00;
    std::uint16_t b = 0x0573;//0000 0101 0111 0011
    std::uint16_t b_z = 0x0000;
    std::uint32_t c = 0x0100F100;// 0000 0001 0000 0000 1111 0001 0000 0000
    std::uint32_t c_z = 0x00000000;
    std::uint64_t d = 0x0000000000040000;//0100 0000 0000 0000 0000
    std::uint64_t d_z = 0x0000000000000000;
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(a),3);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(a_z),0);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(b),7);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(b_z),0);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(c),6);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(c_z),0);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(d),1); 
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::populationCount(d_z),0);
}

TEST(GCCBuiltinMethods,ByteSwap)
{
    using namespace SignalFlux::Platform;
    std::uint16_t b = 0x0573;//0000 0101 0111 0011
    std::uint32_t c = 0x0100F100;// 0000 0001 0000 0000 1111 0001 0000 0000
    std::uint64_t d = 0x0000000000040000;//0100 0000 0000 0000 0000
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::byteSwap(b),0x7305);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::byteSwap(c),0x00F10001);
    EXPECT_EQ(CompilerMethods<CompilerType::GCC>::byteSwap(d),0x0000040000000000);
}
