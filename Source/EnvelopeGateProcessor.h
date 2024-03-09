/*
  ==============================================================================

    EnvelopeGateProcessor.h
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EnvelopeGateProcessor : public juce::AudioProcessor
{
public:
    EnvelopeGateProcessor();
    ~EnvelopeGateProcessor() override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
};