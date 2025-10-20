#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_allocators_buffer_pool.h"


SignumFlux::Allocators::BufferPool<float,128,1024> pool;


TEST(BufferPoolTest,AllocateAndDeallocate)
{
    float * a = pool.allocate(1024);
    ASSERT_NE(a,nullptr);
    pool.deallocate(a,1024);
}

TEST(BufferPoolTest,Reuse)
{
    float * p1 = pool.allocate(1024);
    pool.deallocate(p1,1024);
    float * p2 = pool.allocate(1024);
    ASSERT_EQ(p1,p2);
    pool.deallocate(p2,1024);
}