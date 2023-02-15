/*
  ==============================================================================

    Meter.h
    Created: 14 Feb 2023 5:52:10pm
    Author:  Quessada

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utilities.h"

struct Meter : juce::Component
{
    Meter();
    void paint(juce::Graphics& g) override;
    void update(float dbLevel);

public:
    float peakDb{ NEGATIVE_INFINITY };
};