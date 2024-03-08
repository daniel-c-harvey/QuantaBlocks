/*
  ==============================================================================

    EnvelopeGateEditor.cpp
    Created: 8 Mar 2024 11:15:06am
    Author:  dharvey

  ==============================================================================
*/

#include "EnvelopeGateEditor.h"
#include <JuceHeader.h>

EnvelopeGateEditor::EnvelopeGateEditor(int x, int y) : Component()
{
    sizeX = x;
    sizeY = y;
}

int EnvelopeGateEditor::getSizeX()
{
    return 0;
}

int EnvelopeGateEditor::getSizeY()
{
    return 0;
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
