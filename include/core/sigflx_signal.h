#pragma once
#include <type_traits>
#include <cstddef>
#include <iterator>

namespace SignumFlux
{
template<typename T,typename Allocator>
class Signal
{
public:
    using ValueType = T;
    using SizeType = std::size_t;
    using Pointer = T *;
    using ConstPointer = const T *;
    using Reference = T &;
    using ConstReference = const T &;
    using AllocatorType = Allocator;

    enum class Layout{Interleaved,Planar};

    template<bool isConst>
    class SignalBaseIterator
    {
    public:
        using ValueTypeCondition = typename Signal::ValueType;
        using PointerCondition   = typename std::conditional<isConst,Signal::ConstPointer,Signal::Pointer>::type;
        using ReferenceCondition = typename std::conditional<isConst,Signal::ConstReference,Signal::Reference>::type;

        using IteratorCategory = std::random_access_iterator_tag;
        using ValueType = ValueTypeCondition;
        using SizeType = Signal::SizeType;
        using Pointer = PointerCondition;
        using Reference = ReferenceCondition;
        using DifferenceType = std::ptrdiff_t;
    private:
        Pointer head_ = nullptr;
        SizeType offset_ = 0;
        SizeType frames_ = 0;
        SizeType channels_ = 0;
        Layout layout_ = Layout::Planar;
    public:
        SignalBaseIterator();
        SignalBaseIterator(Pointer head,SizeType offset,SizeType frames,SizeType channels,Layout layout);
        SignalBaseIterator(const SignalBaseIterator & object);
        SignalBaseIterator(SignalBaseIterator && object);

        ~SignalBaseIterator();

        bool operator==(const SignalBaseIterator & object) const;
        bool operator!=(const SignalBaseIterator & object) const;
        bool operator<(const SignalBaseIterator & object) const;
        bool operator>(const SignalBaseIterator & object) const;
        bool operator<=(const SignalBaseIterator & object) const;
        bool operator>=(const SignalBaseIterator & object) const;

        SignalBaseIterator & operator=(const SignalBaseIterator & object);
        SignalBaseIterator & operator=(SignalBaseIterator && object);
        
        SignalBaseIterator operator+(SizeType forward) const;
        SignalBaseIterator operator-(SizeType backward) const;
        DifferenceType operator-(const SignalBaseIterator & object) const;

        SignalBaseIterator & operator+=(SizeType forward);
        SignalBaseIterator & operator-=(SizeType backward);

        SignalBaseIterator & operator++();
        SignalBaseIterator & operator--();
        SignalBaseIterator operator++(int);
        SignalBaseIterator operator--(int);
        

        SizeType currentFrame() const;
        SizeType currentChannel() const;
        Reference operator*() const;
        Pointer operator->() const;
        Reference operator[](DifferenceType n) const;
        
        Pointer head() const { return head_; };
        SizeType offset() const { return offset_; };
        SizeType frames() const { return frames_; };
        SizeType channels() const { return channels_; };
        Layout layout() const {return layout_; };

    }; 

    using SignalIterator = SignalBaseIterator<false>;
    using ConstSignalIterator = SignalBaseIterator<true>;
private:
    Pointer data_ = nullptr;
    SizeType size_ = 0;
    SizeType frames_ = 0;
    SizeType channels_ = 0;
    double sampleRate_ = 1.0;
    double duration_ = 0.0;
    AllocatorType allocator_;
    Layout layout_ = Layout::Planar;
public:
    Signal();
    Signal(const Signal & object);
    Signal(const Signal & object,const AllocatorType & allocator);
    Signal(Signal && object) noexcept;

    Signal(SizeType frames,SizeType channels,double sampleRate,Layout layout = Layout::Planar);
    Signal(SizeType frames,SizeType channels,double sampleRate,const AllocatorType & allocator,Layout layout = Layout::Planar);
    Signal(T * data,SizeType frames,SizeType channels,double sampleRate,Layout layout = Layout::Planar);
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
    Layout layout() const noexcept { return layout_; };
    bool empty() const noexcept { return frames_ == 0 || channels_ == 0; };

    void resize(SizeType newFrames);
    void clear();
    void release();
    void swap(Signal & object);

    void fill(const T & value);

    SignalIterator begin() noexcept;
    SignalIterator end() noexcept;
    ConstSignalIterator begin() const noexcept;
    ConstSignalIterator end() const noexcept;
    ConstSignalIterator cbegin() const noexcept;
    ConstSignalIterator cend() const noexcept;


};

template<typename T,typename Allocator>
void swap(Signal<T,Allocator> & first,Signal<T,Allocator> & second) noexcept;
}

#include "../../src/core/sigflx_signal.tpp"