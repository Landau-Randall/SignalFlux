#include <gtest/gtest.h>
#include "core/sigflx_signal.h"
#include "sigflx_lib/sigflx_allocator.h"


using TestSignal = SignalFlux::Signal<float,SignalFlux::Allocators::AlignedAllocator<float>>;
using Layout = TestSignal::Layout;

TEST(SignalConstruction, DefaultConstructor) 
{
    TestSignal sig;
    EXPECT_TRUE(sig.empty());
    EXPECT_EQ(sig.size(), 0);
    EXPECT_EQ(sig.frames(), 0);
    EXPECT_EQ(sig.channels(), 0);
    EXPECT_EQ(sig.data(), nullptr);
    EXPECT_FALSE(sig.ownsData());
}

TEST(SignalConstruction, SizeBasedConstructor)
{
    TestSignal sig(512,2,44100.0);
    EXPECT_NE(sig.data(),nullptr);
    EXPECT_FALSE(sig.empty());
    EXPECT_EQ(sig.size(),512 * 2);
    EXPECT_EQ(sig.frames(),512);
    EXPECT_EQ(sig.channels(),2);
    EXPECT_EQ(sig.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sig.ownsData());
}

TEST(SignalConstruction, SizeBasedConstructorWithAllocator)
{
    SignalFlux::Allocators::AlignedAllocator<float> alloc;
    TestSignal sig(512,2,44100.0,alloc,Layout::Planar);
    EXPECT_NE(sig.data(),nullptr);
    EXPECT_FALSE(sig.empty());
    EXPECT_EQ(sig.size(),512 * 2);
    EXPECT_EQ(sig.frames(),512);
    EXPECT_EQ(sig.channels(),2);
    EXPECT_EQ(sig.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sig.ownsData());
}

TEST(SignalConstruction, PointerBasedConstructor)
{
    float * testData = new float[512 * 2];
    TestSignal sigOwnsData(testData,512,2,44100.0,true,Layout::Planar);
    TestSignal sigNoOwnsData(testData,512,2,44100.0,false,Layout::Planar);
    EXPECT_NE(sigOwnsData.data(),nullptr);
    EXPECT_NE(sigNoOwnsData.data(),nullptr);
    EXPECT_FALSE(sigOwnsData.empty());
    EXPECT_FALSE(sigNoOwnsData.empty());
    EXPECT_EQ(sigOwnsData.size(),512 * 2);
    EXPECT_EQ(sigNoOwnsData.size(),512 * 2);
    EXPECT_EQ(sigOwnsData.frames(),512);
    EXPECT_EQ(sigNoOwnsData.frames(),512);
    EXPECT_EQ(sigOwnsData.channels(),2);
    EXPECT_EQ(sigNoOwnsData.channels(),2);
    EXPECT_EQ(sigOwnsData.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_EQ(sigNoOwnsData.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sigOwnsData.ownsData());
    EXPECT_FALSE(sigNoOwnsData.ownsData());
    delete [] testData;
}

TEST(SignalConstruction, PointerBasedConstructorWithAllocator)
{
    SignalFlux::Allocators::AlignedAllocator<float> alloc;
    float * testData = new float[512 * 2];
    TestSignal sig(testData,512,2,44100.0,alloc,Layout::Planar);
    EXPECT_NE(sig.data(),nullptr);
    EXPECT_FALSE(sig.empty());
    EXPECT_EQ(sig.size(),512 * 2);
    EXPECT_EQ(sig.frames(),512);
    EXPECT_EQ(sig.channels(),2);
    EXPECT_EQ(sig.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sig.ownsData());
    delete [] testData;
}

TEST(SignalConstruction, CopyConstructor)
{
    float * testData = new float[512 * 2];
    TestSignal sourceSignal(testData,512,2,44100.0,true);
    TestSignal sourceSignalView(testData,512,2,44100.0,false);
    SignalFlux::Allocators::AlignedAllocator<float> alloc;
    TestSignal sigOwnsData(sourceSignal);
    TestSignal sigNoOwnsData(sourceSignalView);
    EXPECT_NE(sigOwnsData.data(),nullptr);
    EXPECT_NE(sigNoOwnsData.data(),nullptr);
    EXPECT_FALSE(sigOwnsData.empty());
    EXPECT_FALSE(sigNoOwnsData.empty());
    EXPECT_EQ(sigOwnsData.size(),512 * 2);
    EXPECT_EQ(sigNoOwnsData.size(),512 * 2);
    EXPECT_EQ(sigOwnsData.frames(),512);
    EXPECT_EQ(sigNoOwnsData.frames(),512);
    EXPECT_EQ(sigOwnsData.channels(),2);
    EXPECT_EQ(sigNoOwnsData.channels(),2);
    EXPECT_EQ(sigOwnsData.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_EQ(sigNoOwnsData.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sigOwnsData.ownsData());
    EXPECT_FALSE(sigNoOwnsData.ownsData());
    delete [] testData;
}

TEST(SignalConstruction, MoveConstructor)
{
    TestSignal sig(512,2,44100.0);
    TestSignal sigMove(std::move(sig));

    EXPECT_TRUE(sig.empty());
    EXPECT_EQ(sig.size(), 0);
    EXPECT_EQ(sig.frames(), 0);
    EXPECT_EQ(sig.channels(), 0);
    EXPECT_EQ(sig.data(), nullptr);
    EXPECT_FALSE(sig.ownsData());

    EXPECT_NE(sigMove.data(),nullptr);
    EXPECT_FALSE(sigMove.empty());
    EXPECT_EQ(sigMove.size(),512 * 2);
    EXPECT_EQ(sigMove.frames(),512);
    EXPECT_EQ(sigMove.channels(),2);
    EXPECT_EQ(sigMove.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sigMove.ownsData());
}

TEST(SignalValuation, SignalValuator)
{
    float * testData = new float[512 * 2];
    TestSignal sourceSignal(testData,512,2,44100.0,true);
    TestSignal sourceSignalView(testData,512,2,44100.0,false);

    TestSignal sigOwnsData;
    TestSignal sigNoOwnsData;
    sigOwnsData = sourceSignal;
    sigNoOwnsData = sourceSignalView;

    EXPECT_NE(sigOwnsData.data(),nullptr);
    EXPECT_NE(sigNoOwnsData.data(),nullptr);
    EXPECT_FALSE(sigOwnsData.empty());
    EXPECT_FALSE(sigNoOwnsData.empty());
    EXPECT_EQ(sigOwnsData.size(),512 * 2);
    EXPECT_EQ(sigNoOwnsData.size(),512 * 2);
    EXPECT_EQ(sigOwnsData.frames(),512);
    EXPECT_EQ(sigNoOwnsData.frames(),512);
    EXPECT_EQ(sigOwnsData.channels(),2);
    EXPECT_EQ(sigNoOwnsData.channels(),2);
    EXPECT_EQ(sigOwnsData.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_EQ(sigNoOwnsData.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sigOwnsData.ownsData());
    EXPECT_FALSE(sigNoOwnsData.ownsData());

    TestSignal sigMove = std::move(sourceSignal);
    EXPECT_NE(sigMove.data(),nullptr);
    EXPECT_FALSE(sigMove.empty());
    EXPECT_EQ(sigMove.size(),512 * 2);
    EXPECT_EQ(sigMove.frames(),512);
    EXPECT_EQ(sigMove.channels(),2);
    EXPECT_EQ(sigMove.duration(),static_cast<double>(512)/(44100.0));
    EXPECT_TRUE(sigMove.ownsData());
    
    delete [] testData;
}

TEST(SignalDataAccess, SignalAccessWithoutRnageCheck)
{
    TestSignal sigPlanar(2,2,44100.0);
    TestSignal sigInverleaved(2,2,44100.0,Layout::Interleaved);

    sigPlanar.data()[0] = 0.1f;
    sigPlanar.data()[1] = 0.2f;
    sigPlanar.data()[2] = 0.3f;
    sigPlanar.data()[3] = 0.4f;

    EXPECT_FLOAT_EQ(sigPlanar(0,0),0.1f);
    EXPECT_FLOAT_EQ(sigPlanar(1,0),0.2f);
    EXPECT_FLOAT_EQ(sigPlanar(0,1),0.3f);
    EXPECT_FLOAT_EQ(sigPlanar(1,1),0.4f);

    sigInverleaved.data()[0] = 0.1f;
    sigInverleaved.data()[1] = 0.2f;
    sigInverleaved.data()[2] = 0.3f;
    sigInverleaved.data()[3] = 0.4f;

    EXPECT_FLOAT_EQ(sigInverleaved(0,0),0.1f);
    EXPECT_FLOAT_EQ(sigInverleaved(0,1),0.2f);
    EXPECT_FLOAT_EQ(sigInverleaved(1,0),0.3f);
    EXPECT_FLOAT_EQ(sigInverleaved(1,1),0.4f);

}

TEST(SignalDataAccess, SignalAccessWithRangeCheck)
{
    TestSignal sig(512,2,44100.0);
    EXPECT_NO_THROW(sig(100,0));
    EXPECT_THROW(sig.at(513,0),std::out_of_range);
    EXPECT_THROW(sig.at(100,2),std::out_of_range);
}

TEST(SignalUtils,SignalFillAndClear)
{
    TestSignal sig(512,2,44100.0);
    sig.fill(0.4f);

    EXPECT_EQ(sig(50,0),0.4f);

    sig.clear();

    EXPECT_EQ(sig(50,0),0.0f);
}

TEST(SignalUtils,SignalResize)
{
    TestSignal sig(20,2,44100.0);
    float * testData = new float[20];
    TestSignal sigView(testData,10,2,44100.0);
    sig.fill(1.0f);

    sig.resize(40);

    EXPECT_EQ(sig(18,0),1.0f);

    sig.resize(10);

    EXPECT_EQ(sig(8,0),1.0f);

    EXPECT_THROW(sigView.resize(30),std::logic_error);
}

TEST(signalUtils,SignalRelease)
{
    TestSignal sig(10,2,44100.0);
    sig.release();
    EXPECT_TRUE(sig.empty());
    EXPECT_EQ(sig.size(), 0);
    EXPECT_EQ(sig.frames(), 0);
    EXPECT_EQ(sig.data(), nullptr);
    EXPECT_FALSE(sig.ownsData());
}
