#pragma once

#include <JuceHeader.h>


template<typename T>
struct Fifo
{
    void prepare(int numChannels, int numSamples)
    {
        static_assert(std::is_same_v<T, juce::AudioBuffer<float>>,
            "prepare(numChannels, numSamples) should only be used when the Fifo is holding juce::AudioBuffer<float>");
        for (auto& buffer : buffers)
        {
            buffer.setSize(numChannels,
                numSamples,
                false,   //clear everything?
                true,    //including the extra space?
                true);   //avoid reallocating if you can?
            buffer.clear();
        }
    }

    void prepare(size_t numElements)
    {
        static_assert(std::is_same_v<T, std::vector<float>>,
            "prepare(numElements) should only be used when the Fifo is holding std::vector<float>");
        for (auto& buffer : buffers)
        {
            buffer.clear();
            buffer.resize(numElements, 0);
        }
    }

    bool push(const T& t)
    {
        auto write = fifo.write(1);
        if (write.blockSize1 > 0)
        {
            buffers[write.startIndex1] = t;
            return true;
        }

        return false;
    }

    bool pull(T& t)
    {
        auto read = fifo.read(1);
        if (read.blockSize1 > 0)
        {
            t = buffers[read.startIndex1];
            return true;
        }

        return false;
    }

    int getNumAvailableForReading() const
    {
        return fifo.getNumReady();
    }
private:
    static constexpr int Size = 30;
    std::array<T, Size> buffers;
    juce::AbstractFifo fifo{ Size };
   
};

//template<typename T, size_t Size>
//struct Fifo
//{
//    size_t getSize() const noexcept { return Size; }
//
//    void prepare(int numSamples, int numChannels)
//    {
//        for (auto& buf : buffer)
//        {
//            buf.setSize(numChannels, numSamples, true, false);
//            buf.clear();
//        }
//    }
//
//    bool push(const T& t)
//    {
//        auto write = fifo.write(1);
//        if (write.blockSize1 > 0)
//        {
//            buffer[write.startIndex1].copyFrom(0, 0, t);
//            return true;
//        }
//
//        return false;
//    }
//
//    bool pull(T& t)
//    {
//        auto read = fifo.read(1);
//        if (read.blockSize1 > 0)
//        {
//            t = buffer[read.startIndex1];
//            return true;
//        }
//
//        return false;
//    }
//
//    int getNumAvailableForReading() const
//    {
//        return fifo.getNumReady();
//    }
//
//    int getAvailableSpace() const
//    {
//        return fifo.getFreeSpace();
//    }
//
//private:
//    juce::AbstractFifo fifo{ Size };
//    juce::AudioBuffer<T> buffer[Size];
//};
