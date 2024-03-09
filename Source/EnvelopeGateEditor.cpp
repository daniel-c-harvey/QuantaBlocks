/*
  ==============================================================================

    EnvelopeGateEditor.cpp
    Created: 8 Mar 2024 11:15:06am
    Author:  dharvey

  ==============================================================================
*/

#include "EnvelopeGateEditor.h"
#include <JuceHeader.h>

EnvelopeGateEditor::EnvelopeGateEditor(EnvelopeGateProcessor& p) 
    : juce::AudioProcessorEditor(&p), processor(p)
{
    // Set default size
    sizeX = 300;
    sizeY = 200;
}

int EnvelopeGateEditor::getSizeX()
{
    return sizeX;
}

int EnvelopeGateEditor::getSizeY()
{
    return sizeY;
}

void EnvelopeGateEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EnvelopeGateEditor::resized()
{
}
