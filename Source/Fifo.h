/*
  ==============================================================================

    Fifo.h
    Created: 14 Feb 2023 6:53:44pm
    Author:  Quessada

  ==============================================================================
*/

#pragma once

//Chuck i just copied over the SImpleMB, i dont know how to write this and understand how it works) asked somethings to chatGPT and modified as it said, but ni dont relaly nknow what everything is for...

#include <JuceHeader.h>


template<typename T, size_t Size>
struct Fifo
{
    size_t getSize() const noexcept { return Size; }

    void prepare(int numSamples, int numChannels)
    {
        for (auto& buf : buffer)
        {
            buf.resize(numChannels, numSamples, true, false);
            buf.clear();
        }
    }

    bool push(const T& t)
    {
        auto write = fifo.write(1);
        if (write.blockSize1 > 0)
        {
            buffer[write.startIndex1] = t;
            return true;
        }

        return false;
    }

    bool pull(T& t)
    {
        auto read = fifo.read(1);
        if (read.blockSize1 > 0)
        {
            t = buffer[read.startIndex1];
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
    juce::AbstractFifo fifo{ Size };
    std::array<T, Size> buffer;
};
