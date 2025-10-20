#include <gtest/gtest.h>
#include <iostream>
#include "sigflx_lib/sigflx_allocators_aligned.h"
#include "core/sigflx_signal.h"

using TestSignal = SignumFlux::Signal<float,SignumFlux::Allocators::AlignedAllocator<float>>;
using Layout = TestSignal::Layout;

TEST(SignalIteratorConstruction,DefaultConstructor)
{
    TestSignal::SignalIterator itr;
    EXPECT_EQ(itr.head(),nullptr);
    EXPECT_EQ(itr.offset(),0);
    EXPECT_EQ(itr.frames(),0);
    EXPECT_EQ(itr.channels(),0);
    EXPECT_EQ(itr.layout(),Layout::Planar);
}

TEST(SignalIteratorConstruction,SizeBasedConstructor)
{
    TestSignal sig(10,2,44100.0);
    auto itrBegin = sig.begin();
    auto itrEnd = sig.end();

    EXPECT_NE(itrBegin.head(),nullptr);
    EXPECT_NE(itrEnd.head(),nullptr);

    EXPECT_EQ(itrBegin.offset(),0);
    EXPECT_EQ(itrEnd.offset(),20);

    EXPECT_EQ(itrBegin.frames(),10);
    EXPECT_EQ(itrEnd.frames(),10);

    EXPECT_EQ(itrBegin.channels(),2);
    EXPECT_EQ(itrEnd.channels(),2);

    EXPECT_EQ(itrBegin.layout(),Layout::Planar);
    EXPECT_EQ(itrEnd.layout(),Layout::Planar);
}

TEST(SignalIteratorConstruction,CopyConstructor)
{
    TestSignal sig(10,2,44100.0);
    auto sourceItr = sig.begin();
    auto itr(sourceItr);

    EXPECT_NE(itr.head(),nullptr);
    EXPECT_EQ(itr.offset(),0);
    EXPECT_EQ(itr.frames(),10);
    EXPECT_EQ(itr.channels(),2);
    EXPECT_EQ(itr.layout(),Layout::Planar);
}   

TEST(SignalIteratorConstruction,MoveConstorctor)
{
    TestSignal sig(10,2,44100.0);
    auto sourceItr = sig.begin();
    auto itr(std::move(sourceItr));

    EXPECT_NE(itr.head(),nullptr);
    EXPECT_EQ(itr.offset(),0);
    EXPECT_EQ(itr.frames(),10);
    EXPECT_EQ(itr.channels(),2);
    EXPECT_EQ(itr.layout(),Layout::Planar);

    EXPECT_EQ(sourceItr.head(),nullptr);
    EXPECT_EQ(sourceItr.offset(),0);
    EXPECT_EQ(sourceItr.frames(),0);
    EXPECT_EQ(sourceItr.channels(),0);
    EXPECT_EQ(sourceItr.layout(),Layout::Planar);
}

TEST(SignalIteratorComparison,ComparisonOverload)
{
    TestSignal sig(10,2,44100.0);
    auto itrBegin = sig.begin();
    auto itrEnd = sig.end();

    EXPECT_FALSE(itrBegin == itrEnd);
    EXPECT_TRUE(itrBegin != itrEnd);
    EXPECT_TRUE(itrBegin < itrEnd);
    EXPECT_FALSE(itrBegin > itrEnd);
    EXPECT_TRUE(itrBegin <= itrEnd);
    EXPECT_FALSE(itrBegin >= itrEnd);
}

TEST(SignalIteratorValuation,CopyValuator)
{
    TestSignal sig(10,2,44100.0);
    auto sourceItr = sig.begin();
    auto itr = sourceItr;

    EXPECT_NE(itr.head(),nullptr);
    EXPECT_EQ(itr.offset(),0);
    EXPECT_EQ(itr.frames(),10);
    EXPECT_EQ(itr.channels(),2);
    EXPECT_EQ(itr.layout(),Layout::Planar);

    EXPECT_NE(sourceItr.head(),nullptr);
    EXPECT_EQ(sourceItr.offset(),0);
    EXPECT_EQ(sourceItr.frames(),10);
    EXPECT_EQ(sourceItr.channels(),2);
    EXPECT_EQ(sourceItr.layout(),Layout::Planar);
}

TEST(SignalIteratorValuation,MoveValuator)
{
    TestSignal sig(10,2,44100.0);
    auto sourceItr = sig.begin();
    auto itr = std::move(sourceItr);

    EXPECT_NE(itr.head(),nullptr);
    EXPECT_EQ(itr.offset(),0);
    EXPECT_EQ(itr.frames(),10);
    EXPECT_EQ(itr.channels(),2);
    EXPECT_EQ(itr.layout(),Layout::Planar);

    EXPECT_EQ(sourceItr.head(),nullptr);
    EXPECT_EQ(sourceItr.offset(),0);
    EXPECT_EQ(sourceItr.frames(),0);
    EXPECT_EQ(sourceItr.channels(),0);
    EXPECT_EQ(sourceItr.layout(),Layout::Planar);
}

TEST(SignalIteratorArithmeticOverload,NonReferenceResult)
{
    TestSignal sig(10,2,44100.0);
    auto itrBegin = sig.begin();
    auto itrEnd = sig.end();

    auto itrPlus = itrBegin + 2;
    auto itrMinus = itrEnd - 2;

    EXPECT_EQ(itrPlus.offset(),2);
    EXPECT_EQ(itrMinus.offset(),18);
    EXPECT_NE(&itrPlus,&itrBegin);
    EXPECT_NE(&itrMinus,&itrEnd);

    auto diff = itrEnd - itrBegin;
    auto diff2 = itrMinus - itrPlus;
    EXPECT_EQ(diff,20);
    EXPECT_EQ(diff2,16);

    auto itrSelfPlus = itrBegin++;
    auto itrSelfMinus = itrEnd--;

    EXPECT_EQ(itrSelfPlus.offset(),0);
    EXPECT_EQ(itrSelfMinus.offset(),20);
    EXPECT_EQ(itrBegin.offset(),1);
    EXPECT_EQ(itrEnd.offset(),19);
    EXPECT_NE(&itrBegin,&itrSelfPlus);
    EXPECT_NE(&itrEnd,&itrSelfMinus);
}

TEST(SignalIteratorArithmeticOverload,ReferenceResult)
{
    TestSignal sig(10,2,44100.0);
    auto itrBegin = sig.begin();
    auto itrEnd = sig.end();

    auto & itrPlus = itrBegin += 2 ;
    auto & itrMinus = itrEnd -= 2;

    EXPECT_EQ(itrPlus.offset(),2);
    EXPECT_EQ(itrMinus.offset(),18);
    EXPECT_EQ(&itrPlus,&itrBegin);
    EXPECT_EQ(&itrMinus,&itrEnd);

    auto & itrSelfPlus = ++itrBegin;
    auto & itrSelfMinus = --itrEnd;
    EXPECT_EQ(itrSelfPlus.offset(),3);
    EXPECT_EQ(itrSelfMinus.offset(),17);
    EXPECT_EQ(&itrBegin,&itrSelfPlus);
    EXPECT_EQ(&itrEnd,&itrSelfMinus);
}

TEST(SignalIteratorUtils,Coordinate)
{
    TestSignal sig(10,2,44100.0);
    auto itr = sig.begin();
    itr += 3;
    auto frame = itr.currentFrame();
    auto channel = itr.currentChannel();
    EXPECT_EQ(frame,1);
    EXPECT_EQ(channel,1);
}

TEST(SignalIteratorUtils,PointerMethod)
{
    TestSignal sig(3,2,44100.0);
    sig(2,1) = 3.5f;
    auto itr = sig.begin();
    itr+= 5;
    EXPECT_EQ(*itr,3.5f);
    EXPECT_EQ(itr[0],3.5f);
    EXPECT_EQ(&(*itr),sig.data() + 5);
    sig.fill(4.0f);
    sig(2,1) = 3.5f;
    for (auto & ele : sig)
    {
        std::cout << ele << ' ';
    }
    std::cout << std::endl;
}