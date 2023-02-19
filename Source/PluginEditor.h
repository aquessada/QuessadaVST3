/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Meter.h"
#include "Fifo.h"
#include "Utilities.h"


//==============================================================================
/**
*/
class QuessadaVST3AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    QuessadaVST3AudioProcessorEditor (QuessadaVST3AudioProcessor&);
    ~QuessadaVST3AudioProcessorEditor() override;

     //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override; // Implement the Timer::timerCallback() function


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    QuessadaVST3AudioProcessor& audioProcessor;
    
    Meter meter;

    juce::AudioBuffer<float> inBuffer;
    
    //static constexpr int Size = 5;
    //Fifo<float, Size> fifo;
    //juce::AudioBuffer<float> buffer;

     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuessadaVST3AudioProcessorEditor)
};
