#pragma once


#pragma once

#include <array>
#include "../JuceLibraryCode/JuceHeader.h"

template<typename T> //, size_t Size>
struct Fifo
{
    size_t getSize() const noexcept
    {
        return Size;
    }

    void prepare(int numSamples, int numChannels)
    {
        for (auto& buffer : buffers)
        {
            buffer.setSize(numChannels, numSamples, false, true, true);
            buffer.clear();
        }
    }

    bool push(const T& t)
    {
        auto scopedWriter = fifo.write(1);
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

    int getAvailableSpace() const
    {
        return fifo.getFreeSpace();
    }

private:
   
    static constexpr int Capacity = 20;
    std::array<T, Capacity> buffers;
    juce::AbstractFifo fifo{ Capacity };
};


//template<typename T>
//struct Fifo
//{
//
//    void prepare(int numberOfChannels, int numberOfSamples)
//    {
//
//        for (auto& buffer : buffers)
//        {
//            buffer.setSize(numberOfChannels, numberOfSamples);
//        }
//
//    }
//
//    bool push(const T& itemToAdd)
//    {
//        auto scopedWriter = fifo.write(1);
//
//        if (scopedWriter.blockSize1 >= 1)
//        {
//            auto& buffer = buffers[scopedWriter.startIndex1];
//            buffer = itemToAdd;
//            return true;
//        }
//
//        return false;
//    }
//
//    bool pull(T& itemToPull)
//    {
//        auto scopedReader = fifo.read(1);
//
//        if (scopedReader.blockSize1 >= 1)
//        {
//            auto& buffer = buffers[scopedReader.startIndex1];
//            itemToPull = buffer;
//            return true;
//        }
//
//        return false;
//    }
//
//private:
//
//    static constexpr int Size = 5;
//    std::array<T, Size> buffers;
//    AbstractFifo fifo{ Size };
//
//};
