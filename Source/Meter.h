/*
  ==============================================================================

    Meter.h
    Created: 14 Feb 2023 5:52:10pm
    Author:  Quessada

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct Meter : juce::Component
{
    Meter();
    void paint(juce::Graphics& g) override;
    void update(float dbLevel);

private:
    static constexpr float NEGATIVE_INFINITY = -72.0f;
    static constexpr float MAX_DECIBELS = 12.0f;
    float peakDb{ NEGATIVE_INFINITY };
};