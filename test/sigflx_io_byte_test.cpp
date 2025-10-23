#include <gtest/gtest.h>
#include "io/sigflx_io_byte.h"


TEST(IOFileMethods,ReadMethod)
{
    using namespace SignumFlux::IO;
    std::uint8_t buffer[30];
    buffer[0] = 0x1;
    buffer[1] = 0x2;
    buffer[2] = 0x3;
    buffer[3] = 0x4;
    buffer[4] = 0x5;
    buffer[5] = 0x6;
    buffer[6] = 0x7;
    buffer[7] = 0x8;
    std::uint16_t test1 = bytesRead<std::uint16_t>(buffer,Endian::Little);
    std::uint16_t test2 = bytesRead<std::uint16_t>(buffer,Endian::Big);
    EXPECT_EQ(test1,0x0201);
    EXPECT_EQ(test2,0x0102);
    std::uint32_t test3 = bytesRead<std::uint32_t>(buffer,Endian::Little);
    std::uint32_t test4 = bytesRead<std::uint32_t>(buffer,Endian::Big);
    EXPECT_EQ(test3,0x04030201);
    EXPECT_EQ(test4,0x01020304);
}

TEST(IOFileMethods,WriteMethod)
{
    using namespace SignumFlux::IO;
    std::uint8_t buffer[30];
    std::uint16_t test1 = 0x1234;
    std::uint32_t test2 = 0x12345678;
    bytesWrite(buffer,test1,Endian::Little);
    bytesWrite(buffer + 2,test1,Endian::Big);
    bytesWrite(buffer + 4,test2,Endian::Little);
    bytesWrite(buffer + 8,test2,Endian::Big);
    EXPECT_EQ(buffer[0],0x34);
    EXPECT_EQ(buffer[2],0x12);
    EXPECT_EQ(buffer[4],0x78);
    EXPECT_EQ(buffer[8],0x12);
}