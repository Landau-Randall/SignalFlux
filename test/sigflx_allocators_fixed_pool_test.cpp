#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_allocators_fixed_pool.h"

TEST(FixedBlockPoolTest, AllocateAndDeallocateChar)
{
    auto& pool = SignalFlux::Allocators::FixedBlockPool::instance();
    char* p = pool.allocate<char>(1);
    ASSERT_NE(p, nullptr);
    pool.deallocate<char>(p, 1);
}

TEST(FixedBlockPoolTest, AllocateAndDeallocateInt64)
{
    auto& pool = SignalFlux::Allocators::FixedBlockPool::instance();
    int64_t* p = pool.allocate<int64_t>(1);
    ASSERT_NE(p, nullptr);
    pool.deallocate<int64_t>(p, 1);
}

TEST(FixedBlockPoolTest, ReuseBlock)
{
    auto& pool = SignalFlux::Allocators::FixedBlockPool::instance();
    char* p1 = pool.allocate<char>(1);
    pool.deallocate<char>(p1, 1);
    char* p2 = pool.allocate<char>(1);
    ASSERT_EQ(p1, p2); // 复用同一个块
    pool.deallocate<char>(p2, 1);
}