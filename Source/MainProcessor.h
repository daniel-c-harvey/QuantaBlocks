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
#include "EnvelopeGroupProcessor.h"

namespace QuantaBlocks
{
    static constexpr int ENVELOPE_COUNT = 2;

    class MainProcessor : public juce::AudioProcessor
    {
    public:
        MainProcessor();
        ~MainProcessor() override;

        //==============================================================================
        void prepareToPlay(double sampleRate, int samplesPerBlock) override;
        void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
        void getStateInformation(juce::MemoryBlock& destData) override;
        void setStateInformation(const void* data, int sizeInBytes) override;

    protected:
        QuantaBlocks::ViewModel<ENVELOPE_COUNT> processor_parameters;
        EnvelopeGroupProcessor<AHREnvelope> envelope;
        
        //==============================================================================
        std::optional<QuantaBlocks::TimeParameters> getHostTimeInfo();

    private:
        juce::AudioProcessorValueTreeState apvts;
    };
}