/*
  ==============================================================================

    EnvelopeGateProcessor.h
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class QuantaBlocksProcessor : public juce::AudioProcessor
{
public:
    QuantaBlocksProcessor();
    ~QuantaBlocksProcessor() override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
};