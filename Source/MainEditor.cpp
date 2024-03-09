/*
  ==============================================================================

    EnvelopeGateEditor.cpp
    Created: 8 Mar 2024 11:15:06am
    Author:  dharvey

  ==============================================================================
*/

#include "MainEditor.h"
#include <JuceHeader.h>

QuantaBlocksEditor::QuantaBlocksEditor(QuantaBlocksProcessor& p) 
    : juce::AudioProcessorEditor(&p), processor(p)
{
    // default size
    setSize(300, 400);
}

void QuantaBlocksEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void QuantaBlocksEditor::resized()
{
    setBounds(getBoundsInParent());
}
