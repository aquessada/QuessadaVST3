/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Meter.h"

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


    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    juce::AudioBuffer<float> buffer;

    Meter meter;

    QuessadaVST3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuessadaVST3AudioProcessorEditor)
};
