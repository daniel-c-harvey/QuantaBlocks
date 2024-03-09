/*
  ==============================================================================

    EnvelopeGateProcessor.cpp
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#include "MainProcessor.h"

EnvelopeGateProcessor::EnvelopeGateProcessor()
    : AudioProcessor (juce::AudioProcessor::BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    )
{
}

EnvelopeGateProcessor::~EnvelopeGateProcessor()
{
}

void EnvelopeGateProcessor::processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&)
{
}
