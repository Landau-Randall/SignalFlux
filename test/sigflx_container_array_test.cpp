#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_container_array.h"

using TestArray = SignalFlux::Container::Array<int,10>;

TEST(ArrayConstructMethod,AllMethod)
{
    TestArray a({1,2,3});
    EXPECT_EQ(a.size(),10);
    EXPECT_NE(a.data(),nullptr);
    EXPECT_FALSE(a.empty());
}

TEST(ArrayAssignmentMethod,AllMethod)
{
    TestArray a({1,2,3});
    TestArray b;
    b = a;
    EXPECT_EQ(b[0],1);
}

TEST(ArrayAccessMethod,WithoutCheck)
{
    TestArray a({1,2,3});
    EXPECT_EQ(a[0],1);
    EXPECT_EQ(a[1],2);
    EXPECT_EQ(a[2],3);
    EXPECT_EQ(a[3],0);
}

TEST(ArrayAccessMethod,WithCheck)
{
    TestArray a({1,2,3});
    EXPECT_EQ(a.at(0),1);
    EXPECT_EQ(a.at(1),2);
    EXPECT_EQ(a.at(2),3);
    EXPECT_EQ(a.at(3),0);
    EXPECT_THROW(a.at(11),std::out_of_range);
}

TEST(ArrayAccessMethod,FirstAndLast)
{
    TestArray a({1,2,3});
    EXPECT_EQ(a.front(),1);
    EXPECT_EQ(a.back(),0);    
}

TEST(ArrayInterface,BaseInterface)
{
    TestArray a({1,2,3});
    EXPECT_NE(a.data(),nullptr);
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(a.size(),10);    
}

TEST(ArrayInterface,AllRangeMethod)
{
    TestArray a({1,2,3});
    TestArray b;
    b.fill(30);
    EXPECT_EQ(b[5],30);
    a.swap(b);
    EXPECT_EQ(a[5],30);
}