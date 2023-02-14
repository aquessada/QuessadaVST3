/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Meter.h"
#include "Fifo.h"



//==============================================================================
QuessadaVST3AudioProcessorEditor::QuessadaVST3AudioProcessorEditor(QuessadaVST3AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), meter()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

        // Create the meter component and add it as a child component
    meter.setBounds(10, 10, 50, getHeight() - 20);

    addAndMakeVisible(&meter); // pass a pointer to the meter object // add the meter as a child component
    setSize (400, 300);

        // Initialize buffer
        buffer.setSize(audioProcessor.getTotalNumInputChannels(), audioProcessor.getSamplesPerBlock(), false);

    //set timer construct for the rms level meters
    startTimerHz(60);
}

QuessadaVST3AudioProcessorEditor::~QuessadaVST3AudioProcessorEditor()
{
}

//==============================================================================
void QuessadaVST3AudioProcessorEditor::paint (juce::Graphics& g) 
{
    //// (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // Draw the background of the plugin GUI
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    // Calculate the y position of the rectangle based on the peakDb value
    float height = static_cast<float>(getHeight());
    float y = juce::jmap(meter.peakDb, NEGATIVE_INFINITY, MAX_DECIBELS, height, 0.0f);


    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

      // Draw the meter
    meter.update(0.0f);
    meter.paint(g);
}

void QuessadaVST3AudioProcessorEditor::timerCallback()
{
    //if (audioProcessor.fifo.getNumAvailableForReading() > 0)  //dont know what are the available items to put here!!!
  // Check if the fifo has items available for reading
    if (audioProcessor.fifo.getNumAvailableForReading() > 0)
    {
        // Pull every element available out of the fifo
        while (audioProcessor.fifo.pull(buffer))
        {
        }


void QuessadaVST3AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
        // Set the bounds of the meter component
    meter.setBounds(10, 10, 50, getHeight() - 20);
 
}

