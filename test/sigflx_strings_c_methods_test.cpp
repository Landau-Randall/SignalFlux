#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_strings_c_methods.h"

TEST(CStringMethods,StringLength)
{
    using namespace SignalFlux::Strings;
    const char * test1 = "abcd";
    const wchar_t * test2 = L"abcde";
    std::size_t size_a = stringLength(test1);
    std::size_t size_b = stringLength(test2);
    EXPECT_EQ(size_a,4);
    EXPECT_EQ(size_b,5);
}

TEST(CStringMethods,StringCopy)
{
    using namespace SignalFlux::Strings;
    const char * test1 = "abcd";
    const wchar_t * test2 = L"abcde";
    char buffer1[5];
    wchar_t buffer2[6];
    stringCopy(buffer1,test1,5);
    stringCopy(buffer2,test2,6);
    EXPECT_STREQ(buffer1,test1);
    EXPECT_STREQ(buffer2,test2);
}

TEST(CStringMethods,AllStringCompare)
{
    using namespace SignalFlux::Strings;
    const char * test1 = "abcd";
    const char * test2 = "bcde";
    const char * test3 = "abcd";
    const char * test4 = nullptr;
    int sign1 = stringCompare(test1,test2);
    int sign2 = stringCompare(test2,test3);
    int sign3 = stringCompare(test1,test3);
    int sign4 = stringCompare(test1,test4);
    EXPECT_EQ(sign1,-1);
    EXPECT_EQ(sign2,1);
    EXPECT_EQ(sign3,0);
    EXPECT_EQ(sign4,-2);
}

TEST(CStringMethods,PartStringCompare)
{
    using namespace SignalFlux::Strings;
    const char * test1 = "abcd";
    const char * test2 = "abce";
    int sign1 = stringCompare(test1,test2);
    int sign2 = stringCompare(test1,test2,4);
    int sign3 = stringCompare(test2,test1);
    EXPECT_EQ(sign1,-1);
    EXPECT_EQ(sign2,-1);
    EXPECT_EQ(sign3,1);
}

TEST(CStringMethods,StringFind)
{
    using namespace SignalFlux::Strings;
    const char * test1 = "abedef";
    const char * sign1 = stringFind(test1,'e');
    const char * sign2 = stringFind(test1,"de");
    const char * sign3 = stringFind(test1,'\0');
    EXPECT_EQ(sign1,&test1[2]);
    EXPECT_EQ(sign2,&test1[3]);
    EXPECT_EQ(sign3,nullptr);
}

TEST(CstringMethods,StringFill)
{
    using namespace SignalFlux::Strings;
    char buffer[6];
    const char * test1 = "aaaaa";
    stringFill(buffer,'a',5);
    buffer[5] = '\0';
    EXPECT_STREQ(buffer,test1);
}