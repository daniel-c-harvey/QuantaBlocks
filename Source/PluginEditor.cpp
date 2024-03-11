/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
QuantaBlocksAudioProcessorEditor::QuantaBlocksAudioProcessorEditor (QuantaBlocksAudioProcessor& p)
    : QuantaBlocks::MainEditor(p), audioProcessor (p)
{
}

QuantaBlocksAudioProcessorEditor::~QuantaBlocksAudioProcessorEditor()
{
}

//==============================================================================
void QuantaBlocksAudioProcessorEditor::paint (juce::Graphics& g)
{
    MainEditor::paint(g);
}

void QuantaBlocksAudioProcessorEditor::resized()
{
    MainEditor::resized();
}
