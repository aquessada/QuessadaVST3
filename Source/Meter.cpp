/*
  ==============================================================================

    Meter.cpp
    Created: 14 Feb 2023 5:52:10pm
    Author:  Quessada

  ==============================================================================
*/

#include "Meter.h"
#include <JuceHeader.h>
#include "Utilities.h"

Meter::Meter()
{
    setOpaque(true); // make sure paint() covers the entire area
}

void Meter::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // fill with background color
    g.setColour(juce::Colours::white);

    auto area = getLocalBounds();
    auto y = area.getBottom() - area.getHeight() * (peakDb - NEGATIVE_INFINITY) / (MAX_DECIBELS - NEGATIVE_INFINITY); // map peakDb to a position within the component
    //g.fillRect(0, y, area.getWidth(), area.getBottom() - y); // draw the rectangle
    g.fillRect(0.0f, static_cast<float>(y), static_cast<float>(area.getWidth()), static_cast<float>(area.getBottom() - y)); // draw the rectangle
    // draw the rectangle
}

void Meter::update(float dbLevel)
{
    peakDb = dbLevel; //commented out the smoothing > peakDb ? dbLevel : peakDb * 0.99f; // update peakDb with a smoothing factor
    repaint(); // request a repaint
}
