#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_container_vector_view.h"

using namespace SignumFlux::Container;
using TestView = VectorView<std::uint8_t>;

TEST(VectorViewTest,ConstructMethod)
{
    TestView a;
    EXPECT_EQ(a.data(),nullptr);
    EXPECT_EQ(a.size(),0);
    std::uint8_t arr[10];
    TestView b(arr,10);
    EXPECT_EQ(b.data(),&arr[0]);
    EXPECT_EQ(b.size(),10);
    TestView c(b);
    EXPECT_EQ(c.data(),&arr[0]);
    EXPECT_EQ(c.size(),10);
    TestView d(std::move(b));
    EXPECT_EQ(d.data(),&arr[0]);
    EXPECT_EQ(d.size(),10);
}

TEST(VectorViewTest,AssignMethod)
{
    TestView a;
    std::uint8_t arr[10];
    TestView b(arr,10);
    a = b;
    EXPECT_EQ(a.data(),&arr[0]);
    EXPECT_EQ(a.size(),10);
    TestView c;
    c = std::move(b);
    EXPECT_EQ(c.data(),&arr[0]);
    EXPECT_EQ(c.size(),10);
}

TEST(VectorViewTest,AccessMethod)
{
    std::uint8_t arr[10];
    arr[0] = 10;
    arr[4] = 11;
    TestView a(arr,10);
    EXPECT_EQ(a[0],10);
    arr[0] = 31;
    EXPECT_EQ(a[0],31);
    EXPECT_EQ(a.at(0),31);
    EXPECT_THROW(a.at(20),std::out_of_range);
}

TEST(VectorViewTest,IteratorMethod)
{
    std::uint8_t arr[10];
    TestView a(arr,10);
    EXPECT_EQ(a.begin(),&arr[0]);
    EXPECT_EQ(a.end(), &arr[0] + 10);
}