/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
QuantaBlocksAudioProcessorEditor::QuantaBlocksAudioProcessorEditor (QuantaBlocksAudioProcessor& p)
    : QuantaBlocksEditor(p), audioProcessor (p) 
{
}

QuantaBlocksAudioProcessorEditor::~QuantaBlocksAudioProcessorEditor()
{
}

//==============================================================================
void QuantaBlocksAudioProcessorEditor::paint (juce::Graphics& g)
{
    QuantaBlocksEditor::paint(g);
}

void QuantaBlocksAudioProcessorEditor::resized()
{
    QuantaBlocksEditor::resized();
}
