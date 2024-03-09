/*
  ==============================================================================

    EnvelopeGateProcessor.cpp
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#include "MainProcessor.h"

QuantaBlocksProcessor::QuantaBlocksProcessor()
    : AudioProcessor (juce::AudioProcessor::BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    )
{
}

QuantaBlocksProcessor::~QuantaBlocksProcessor()
{
}

void QuantaBlocksProcessor::processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&)
{
}
