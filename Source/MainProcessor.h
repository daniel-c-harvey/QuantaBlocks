/*
  ==============================================================================

    EnvelopeGateProcessor.h
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ViewModel.h"

class QuantaBlocksProcessor : public juce::AudioProcessor
{
public:
    QuantaBlocksProcessor();
    ~QuantaBlocksProcessor() override;

    //==============================================================================
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    //==============================================================================
    QuantaBlocksViewModel parameters;
    juce::AudioProcessorValueTreeState apvts;
};