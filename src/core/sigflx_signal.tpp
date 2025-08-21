#include "core/sigflx_signal.h"
#include <algorithm>
#include <stdexcept>

namespace SignalFlux
{
template<typename T,typename Allocator>
Signal<T,Allocator>::Signal()
{

}

template <typename T, typename Allocator>
Signal<T, Allocator>::Signal(const Signal &object): 
size_(object.size_),
frames_(object.frames_),
channels_(object.channels_),
sampleRate_(object.sampleRate_),
duration_(object.duration_),
allocator_(object.allocator_),
layout_(object.layout_),
ownsData_(object.ownsData_)
{
    if (ownsData_)
    {
        if (object.data_ != nullptr)
        {
            data_ = allocator_.allocate(size_);
            std::copy(object.data_,object.data_ + object.size_,data_);
        }
    }
    else
    {
        if (object.data_ != nullptr)
        {
            data_ = object.data_;
        }
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(const Signal & object,const AllocatorType & allocator):
size_(object.size_),
frames_(object.frames_),
channels_(object.channels_),
sampleRate_(object.sampleRate_),
duration_(object.duration_),
allocator_(allocator),
layout_(object.layout_),
ownsData_(true)
{
    if (object.data_ != nullptr)
    {
        data_ = allocator_.allocate(size_);
        std::copy(object.data_,object.data_ + object.size_,data_);
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(Signal && object) noexcept:
data_(object.data_),
size_(object.size_),
frames_(object.frames_),
channels_(object.channels_),
sampleRate_(object.sampleRate_),
duration_(object.duration_),
allocator_(std::move(object.allocator_)),
layout_(object.layout_),
ownsData_(object.ownsData_)
{
    object.data_ = nullptr;
    object.size_ = 0;
    object.frames_ = 0;
    object.channels_ = 0;
    object.sampleRate_ = 1.0;
    object.duration_ = 0.0;
    object.layout_ = Layout::Planar;
    object.ownsData_ = false;
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(SizeType frames,SizeType channels,double sampleRate,Layout layout):
size_(frames * channels),
frames_(frames),
channels_(channels),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_(),
ownsData_(true),
layout_(layout)
{
    data_ = allocator_.allocate(size_);
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(SizeType frames,SizeType channels,double sampleRate,const AllocatorType & allocator,Layout layout):
size_(frames * channels),
frames_(frames),
channels_(channels),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_(allocator),
ownsData_(true),
layout_(layout)
{
    data_ = allocator_.allocate(size_);
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(T * data,SizeType frames,SizeType channels,double sampleRate,bool ownsData,Layout layout):
size_(frames * channels),
frames_(frames),channels_(channels),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_(),
ownsData_(ownsData),
layout_(layout)
{
    if (ownsData_)
    {
        if (data != nullptr)
        {
            data_ = allocator_.allocate(size_);
            std::copy(data,data + size_,data_);
        }
    }
    else
    {
        if (data != nullptr)
        {
            data_ = data;
        }
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(T * data,SizeType frames,SizeType channels,double sampleRate,const AllocatorType & allocator,Layout layout):
size_(frames * channels),
frames_(frames),
channels_(channels),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_(allocator),
ownsData_(true),
layout_(layout)
{
    if (data != nullptr)
    {
        data_ = allocator_.allocate(size_);
        std::copy(data,data + size_,data_);
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::~Signal()
{
    if (ownsData_)
    {
        if (data_ != nullptr)
        {
            allocator_.deallocate(data_,size_);
            data_ = nullptr;
        }
    }
    else
    {
        data_ = nullptr;
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator> & Signal<T,Allocator>::operator=(const Signal & object)
{
    Signal temp(object);
    swap(temp);
    return *this;
}

template<typename T,typename Allocator>
Signal<T,Allocator> & Signal<T,Allocator>::operator=(Signal && object) noexcept
{
    if (this != &object)
    {
        Signal temp;
        swap(temp);
        swap(object);
    }
    return *this; 
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::Reference Signal<T,Allocator>::operator()(SizeType frame,SizeType channel)
{
    SizeType sign = static_cast<SizeType>(layout_); 
    SizeType offset = sign * (frame + channel * frames_) + (1 - sign) * (frame * channels_ + channel);
    return data_[offset];
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstReference Signal<T,Allocator>::operator()(SizeType frame,SizeType channel) const
{
    SizeType sign = static_cast<SizeType>(layout_); 
    SizeType offset = sign * (frame + channel * frames_) + (1 - sign) * (frame * channels_ + channel);
    return data_[offset];
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::Reference Signal<T,Allocator>::at(SizeType frame,SizeType channel)
{
    if (frame < frames_ && channel < channels_)
    {
        SizeType sign = static_cast<SizeType>(layout_); 
        SizeType offset = sign * (frame + channel * frames_) + (1 - sign) * (frame * channels_ + channel);
        return data_[offset];
    }
    else
    {
        throw std::out_of_range("frame or channel out of range!");
    }
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstReference Signal<T,Allocator>::at(SizeType frame,SizeType channel) const
{
    if (frame < frames_ && channel < channels_)
    {
        SizeType sign = static_cast<SizeType>(layout_); 
        SizeType offset = sign * (frame + channel * frames_) + (1 - sign) * (frame * channels_ + channel);
        return data_[offset];
    }
    else
    {
        throw std::out_of_range("frame or channel out of range!");
    }
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::resize(SizeType newFrames)
{
    if (!ownsData_)
    {
        throw std::logic_error("resize must owns the data!");
    }

    if (newFrames == frames_)
    {
        return;
    }

    const SizeType newSize = newFrames * channels_;

    if (newSize == 0)
    {
        release();
        return;
    }

    Pointer newData = allocator_.allocate(newSize);

    if (data_ != nullptr)
    {
        const SizeType framesToCopy = std::min(frames_, newFrames);
        const SizeType sizeToCopy = framesToCopy * channels_;
        std::copy(data_, data_ + sizeToCopy, newData);

        allocator_.deallocate(data_, size_);
    }

    data_ = newData;
    frames_ = newFrames;
    size_ = newSize;
    duration_ = (sampleRate_ > 0) ? static_cast<double>(frames_) / sampleRate_ : 0.0;
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::clear()
{
    fill(T(0));
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::release()
{
    if (ownsData_)
    {
        if (data_ != nullptr)
        {
            allocator_.deallocate(data_,size_);
            data_ = nullptr;
        }
        size_ = 0;
        frames_ = 0;
        duration_ = 0.0;
        ownsData_ = false;
    }
    else
    {
        data_ = nullptr;
        size_ = 0;
        frames_ = 0;
        duration_ = 0.0;
    }
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::swap(Signal & second)
{
    std::swap(data_,second.data_);
    std::swap(size_,second.size_);
    std::swap(frames_,second.frames_);
    std::swap(channels_,second.channels_);
    std::swap(sampleRate_,second.sampleRate_);
    std::swap(duration_,second.duration_);
    std::swap(allocator_,second.allocator_);
    std::swap(ownsData_,second.ownsData_);
    std::swap(layout_,second.layout_);
}


template<typename T,typename Allocator>
void Signal<T,Allocator>::fill(const T & value)
{
    if (data_ != nullptr)
    {
        std::fill(data_,data_ + size_,value);
    }
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::SignalIterator Signal<T,Allocator>::begin() noexcept
{
    return SignalIterator(data_,0,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::SignalIterator Signal<T,Allocator>::end() noexcept
{
    return SignalIterator(data_,size_,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstSignalIterator Signal<T,Allocator>::begin() const noexcept
{
    return ConstSignalIterator(data_,0,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstSignalIterator Signal<T,Allocator>::end() const noexcept
{
    return ConstSignalIterator(data_,size_,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstSignalIterator Signal<T,Allocator>::cbegin() const noexcept
{
    return ConstSignalIterator(data_,0,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstSignalIterator Signal<T,Allocator>::cend() const noexcept
{
    return ConstSignalIterator(data_,size_,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
void swap(Signal<T,Allocator> & first,Signal<T,Allocator> & second) noexcept
{
    first.swap(second);
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst>::SignalBaseIterator()
{

}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst>::SignalBaseIterator(Pointer head,SizeType offset,SizeType frames,SizeType channels,Layout layout):
head_(head),
offset_(offset),
frames_(frames),
channels_(channels),
layout_(layout)
{

}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst>::SignalBaseIterator(const SignalBaseIterator & object):
head_(object.head_),
offset_(object.offset_),
frames_(object.frames_),
channels_(object.channels_),
layout_(object.layout_)
{

}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst>::SignalBaseIterator(SignalBaseIterator && object):
head_(object.head_),
offset_(object.offset_),
frames_(object.frames_),
channels_(object.channels_),
layout_(object.layout_)
{
    object.head_ = nullptr;
    object.offset_ = 0;
    object.frames_ = 0;
    object.channels_ = 0;
    object.layout_ = Layout::Planar;
}


template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst>::~SignalBaseIterator()
{
    head_ = nullptr;
    offset_ = 0;
    frames_ = 0;
    channels_ = 0;
    layout_ = Layout::Planar;
}

template<typename T,typename Allocator>
template<bool isConst>
bool Signal<T,Allocator>::SignalBaseIterator<isConst>::operator==(const SignalBaseIterator & object) const
{
    return (head_ == object.head_) && (offset_ == object.offset_);
}

template<typename T,typename Allocator>
template<bool isConst>
bool Signal<T,Allocator>::SignalBaseIterator<isConst>::operator!=(const SignalBaseIterator & object) const
{
    return !(*this == object);
}

template<typename T,typename Allocator>
template<bool isConst>
bool Signal<T,Allocator>::SignalBaseIterator<isConst>::operator<(const SignalBaseIterator & object) const
{
    return offset_ < object.offset_;
}

template<typename T,typename Allocator>
template<bool isConst>
bool Signal<T,Allocator>::SignalBaseIterator<isConst>::operator>(const SignalBaseIterator & object) const
{
    return offset_ > object.offset_;
}

template<typename T,typename Allocator>
template<bool isConst>
bool Signal<T,Allocator>::SignalBaseIterator<isConst>::operator<=(const SignalBaseIterator & object) const
{
    return offset_ <= object.offset_;
}

template<typename T,typename Allocator>
template<bool isConst>
bool Signal<T,Allocator>::SignalBaseIterator<isConst>::operator>=(const SignalBaseIterator & object) const
{
    return offset_ >= object.offset_;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> & Signal<T,Allocator>::SignalBaseIterator<isConst>::operator=(const SignalBaseIterator & object)
{
    if (*this != object)
    {
        head_ = object.head_;
        offset_ = object.offset_;
        frames_ = object.frames_;
        channels_ = object.channels_;
        layout_ = object.layout_;
    }
    return *this;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> & Signal<T,Allocator>::SignalBaseIterator<isConst>::operator=(SignalBaseIterator && object)
{
    if (this != &object)
    {
        head_ = object.head_;
        offset_ = object.offset_;
        frames_ = object.frames_;
        channels_ = object.channels_;
        layout_ = object.layout_;

        object.head_ = nullptr;
        object.offset_ = 0;
        object.frames_ = 0;
        object.channels_ = 0;
        object.layout_ = Layout::Planar;
    }
    return *this;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> Signal<T,Allocator>::SignalBaseIterator<isConst>::operator+(SizeType forward) const
{
    return SignalBaseIterator(head_,offset_ + forward,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> Signal<T,Allocator>::SignalBaseIterator<isConst>::operator-(SizeType backward) const
{
    return SignalBaseIterator(head_,offset_ - backward,frames_,channels_,layout_);
}

template<typename T,typename Allocator>
template<bool isConst>
typename Signal<T,Allocator>::SignalBaseIterator<isConst>::DifferenceType Signal<T,Allocator>::SignalBaseIterator<isConst>::operator-(const SignalBaseIterator & object) const
{
    return offset_ - object.offset_;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> & Signal<T,Allocator>::SignalBaseIterator<isConst>::operator+=(SizeType forward) 
{
    offset_+= forward;
    return *this;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> & Signal<T,Allocator>::SignalBaseIterator<isConst>::operator-=(SizeType backward) 
{
    offset_-= backward;
    return *this;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> & Signal<T,Allocator>::SignalBaseIterator<isConst>::operator++()
{
    offset_++;
    return *this;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> & Signal<T,Allocator>::SignalBaseIterator<isConst>::operator--()
{
    offset_--;
    return *this;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> Signal<T,Allocator>::SignalBaseIterator<isConst>::operator++(int)
{
    SignalBaseIterator temp = *this;
    ++offset_;
    return temp;
}

template<typename T,typename Allocator>
template<bool isConst>
Signal<T,Allocator>::SignalBaseIterator<isConst> Signal<T,Allocator>::SignalBaseIterator<isConst>::operator--(int)
{
    SignalBaseIterator temp = *this;
    --offset_;
    return temp;
}

template<typename T,typename Allocator>
template<bool isConst>
typename Signal<T,Allocator>::SignalBaseIterator<isConst>::SizeType Signal<T,Allocator>::SignalBaseIterator<isConst>::currentFrame() const
{
    return offset_ / channels_;
}

template<typename T,typename Allocator>
template<bool isConst>
typename Signal<T,Allocator>::SignalBaseIterator<isConst>::SizeType Signal<T,Allocator>::SignalBaseIterator<isConst>::currentChannel() const
{
    return offset_ % channels_;
}

template<typename T,typename Allocator>
template<bool isConst>
typename Signal<T,Allocator>::SignalBaseIterator<isConst>::Reference Signal<T,Allocator>::SignalBaseIterator<isConst>::operator*() const
{
    SizeType frame = currentFrame();
    SizeType channel = currentChannel();
    SizeType currentLayout = static_cast<SizeType>(layout_);
    SizeType realOffset = (1 - currentLayout) * (offset_) + (currentLayout) * (channel * frames_ + frame);
    return head_[realOffset];
}

template<typename T,typename Allocator>
template<bool isConst>
typename Signal<T,Allocator>::SignalBaseIterator<isConst>::Pointer Signal<T,Allocator>::SignalBaseIterator<isConst>::operator->() const
{
    return &(operator*());
}

template<typename T,typename Allocator>
template<bool isConst>
typename Signal<T,Allocator>::SignalBaseIterator<isConst>::Reference Signal<T,Allocator>::SignalBaseIterator<isConst>::operator[](DifferenceType n) const
{
    return *(*this + n);
}
}