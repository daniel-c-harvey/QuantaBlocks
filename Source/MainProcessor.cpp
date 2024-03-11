/*
  ==============================================================================

    EnvelopeGateProcessor.cpp
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#include "MainProcessor.h"


QuantaBlocksProcessor::QuantaBlocksProcessor()
    : AudioProcessor(juce::AudioProcessor::BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    ), apvts(*this, nullptr, "Parameters", QuantaBlocksViewModel::createParameterLayout())
{
}

QuantaBlocksProcessor::~QuantaBlocksProcessor()
{
}

void QuantaBlocksProcessor::processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&)
{
}

void QuantaBlocksProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void QuantaBlocksProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        // load parameters
        apvts.state = tree;
    }
}