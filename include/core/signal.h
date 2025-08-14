#pragma once

namespace SignalFlux
{
template<typename T,typename Allocator>
class Signal
{
    T * data_ = nullptr;
    std::size_t size_ = 0;
    double sampleRate_ = 1.0;
    std::size_t channel_ = 0;
    std::size_t frames = 0;
    double duration_ = 0.0;
};
}

