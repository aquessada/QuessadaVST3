/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Meter.h"
#include "Utilities.h"
#include "Fifo.h"


//==============================================================================
QuessadaVST3AudioProcessorEditor::QuessadaVST3AudioProcessorEditor(QuessadaVST3AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), meter()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    // Create the meter component and add it as a child component
    meter.setBounds(10, 10, 50, getHeight() - 20);

    // Add the meter as a child component and make it visible
    addAndMakeVisible(meter); 

        // Initialize buffer
    buffer.setSize(audioProcessor.getTotalNumInputChannels(), audioProcessor.getBlockSize(), false);


    //set timer construct for the rms level meters
    startTimerHz(60);
}

QuessadaVST3AudioProcessorEditor::~QuessadaVST3AudioProcessorEditor()
{
}

//==============================================================================
void QuessadaVST3AudioProcessorEditor::paint (juce::Graphics& g) 
{
    using namespace juce;

    // Draw the background of the plugin GUI
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
   
    // Calculate the y position of the rectangle based on the peakDb value
    float height = static_cast<float>(getHeight());
    auto y = jmap(meter.peakDb, NEGATIVE_INFINITY, MAX_DECIBELS, height, 0.0f);


    // Draw the meter
    meter.update(0.0f);
    meter.paint(g);

}

void QuessadaVST3AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
        // Set the bounds of the meter component
    meter.setBounds(10, 10, 50, getHeight() - 20);

}

void QuessadaVST3AudioProcessorEditor::timerCallback()
{
    // Check if the fifo has items available for reading
    if (fifo.getNumAvailableForReading() > 0)
    {
        // Pull every element available out of the fifo
        while (fifo.pull(buffer))
        {
            // Get the magnitude of the left channel
            float leftMagnitude = buffer.getMagnitude(0, 0, buffer.getNumSamples());

            // Convert the magnitude to decibels
            float leftDb = juce::Decibels::gainToDecibels(leftMagnitude, NEGATIVE_INFINITY);

            // Pass the decibel value to the Meter using the update() function
            meter.update(leftDb);
        }
    }
}







