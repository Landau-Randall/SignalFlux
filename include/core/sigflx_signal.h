#pragma once
#include <cstddef>

namespace SignalFlux
{
template<typename T,typename Allocator>
class Signal
{
public:
    using ValueType = T;
    using Pointer = T *;
    using ConstPointer = const T *;
    using Reference = T &;
    using ConstReference = const T &;
    using SizeType = std::size_t;
    using AllocatorType = Allocator;

    enum class Layout{Interleaved,Planar};
private:
    Pointer data_ = nullptr;
    SizeType size_ = 0;
    SizeType frames_ = 0;
    SizeType channels_ = 0;
    double sampleRate_ = 1.0;
    double duration_ = 0.0;
    AllocatorType allocator_;
    bool ownsData_ = false;
    Layout layout_ = Layout::Planar;
public:
    Signal();
    Signal(const Signal & object);
    Signal(const Signal & object,const AllocatorType & allocator);
    Signal(Signal && object) noexcept;

    Signal(SizeType frames,SizeType channels,double sampleRate,Layout layout = Layout::Planar);
    Signal(SizeType frames,SizeType channels,double sampleRate,const AllocatorType & allocator,Layout layout = Layout::Planar);
    Signal(T * data,SizeType frames,SizeType channels,double sampleRate,bool ownsData = false,Layout layout = Layout::Planar);
    Signal(T * data,SizeType frames,SizeType channels,double sampleRate,const AllocatorType & allocator,Layout layout = Layout::Planar);

    ~Signal();

    Signal & operator=(const Signal & object);
    Signal & operator=(Signal && object) noexcept;

    Reference operator()(SizeType frame,SizeType channel);
    ConstReference operator()(SizeType frame,SizeType channel) const;
    Reference at(SizeType frame,SizeType channel);
    ConstReference at(SizeType frame,SizeType channel) const;

    Pointer data() noexcept { return data_; };
    ConstPointer data() const noexcept { return data_; };
    SizeType size() const noexcept { return size_; };
    SizeType frames() const noexcept { return frames_; };
    SizeType channels() const noexcept { return channels_; };
    double sampleRate() const noexcept { return sampleRate_; };
    double duration() const noexcept { return duration_; };
    bool ownsData() const noexcept { return ownsData_; };
    Layout layout() const noexcept { return layout_; };
    bool empty() const noexcept { return size_ == 0; };

    void resize(SizeType newFrames);
    void clear();
    void release();
    void swap(Signal & object);

    void fill(const T & value);

};

template<typename T,typename Allocator>
void swap(Signal<T,Allocator> & first,Signal<T,Allocator> & second) noexcept;
}

#include "../../src/core/sigflx_signal.tpp"