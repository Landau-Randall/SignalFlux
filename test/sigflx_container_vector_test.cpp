#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_container_vector.h"

using namespace SignumFlux::Container;

TEST(VectorTest,ConstructMethod)
{
    Vector<float> a;
    EXPECT_EQ(a.data(),nullptr);
    EXPECT_EQ(a.size(),0);
    EXPECT_EQ(a.capacity(),0);

    Vector<float> b(3,1.3f);
    EXPECT_NE(b.data(),nullptr);
    EXPECT_EQ(b.size(),3);
    EXPECT_EQ(b.capacity(),6);

    Vector<float> c(b);
    EXPECT_NE(c.data(),nullptr);
    EXPECT_EQ(c.size(),3);
    EXPECT_EQ(c.capacity(),6);

    Vector<float> d(std::move(b));
    EXPECT_NE(d.data(),nullptr);
    EXPECT_EQ(d.size(),3);
    EXPECT_EQ(d.capacity(),6);
    EXPECT_EQ(b.data(),nullptr);
    EXPECT_EQ(b.size(),0);
    EXPECT_EQ(b.capacity(),0);

    Vector<float> e({1.0f,2.0f,3.0f});
    EXPECT_NE(e.data(),nullptr);
    EXPECT_EQ(e.size(),3);
    EXPECT_EQ(e.capacity(),6);
}

TEST(VectorTest,AssignmentMethod)
{  
    Vector<float> a;
    Vector<float> b(3,1.3f);
    a = b;
    EXPECT_NE(a.data(),nullptr);
    EXPECT_EQ(a.size(),3);
    EXPECT_EQ(a.capacity(),6);

    Vector<float> c;
    c = std::move(b);    
    EXPECT_NE(c.data(),nullptr);
    EXPECT_EQ(c.size(),3);
    EXPECT_EQ(c.capacity(),6);
    EXPECT_EQ(b.data(),nullptr);
    EXPECT_EQ(b.size(),0);
    EXPECT_EQ(b.capacity(),0);
}

TEST(VectorTest,AccessMethod)
{
    Vector<float> a(10,3.0f);
    a[1] = 1.0;
    EXPECT_FLOAT_EQ(a[1],1.0f);
    EXPECT_FLOAT_EQ(a.at(1),1.0f);
    EXPECT_THROW(a.at(12),std::out_of_range);
    EXPECT_FLOAT_EQ(a.front(),3.0f);
    EXPECT_FLOAT_EQ(a.back(),3.0f);
}

TEST(VectorTest,ChangeMethod)
{
    Vector<float> a;
    a.reserve(10);
    EXPECT_NE(a.data(),nullptr);
    EXPECT_EQ(a.size(),0);
    EXPECT_EQ(a.capacity(),10);
    a.resize(3);
    EXPECT_NE(a.data(),nullptr);
    EXPECT_FLOAT_EQ(a[1],0.0f);
    EXPECT_EQ(a.size(),3);
    EXPECT_EQ(a.capacity(),10);
    a.pushBack(3.14f);
    EXPECT_NE(a.data(),nullptr);
    EXPECT_EQ(a.size(),4);
    EXPECT_EQ(a.capacity(),10);
    EXPECT_FLOAT_EQ(a.back(),3.14f);
    a.popBack();
    EXPECT_NE(a.data(),nullptr);
    EXPECT_EQ(a.size(),3);
    EXPECT_EQ(a.capacity(),10);
    EXPECT_NE(a.back(),3.14f);
    a.shrinkToFit();
    EXPECT_NE(a.data(),nullptr);
    EXPECT_EQ(a.size(),3);
    EXPECT_EQ(a.capacity(),3);
}