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

namespace QuantaBlocks
{
    static constexpr int ENVELOPE_COUNT = 1;

    struct BlockParameters
    {
        int block_length;
        float sample_rate;
        float dt;
        float sec_per_beat;
        float ms_per_beat;
        float pulse_per_beat;
        float ms_per_pulse;

        double tempo;
        double pulse_position;
        int timesignature_denominator;
    };

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
    
        //==============================================================================

        bool getHostTimeInfo();
        QuantaBlocks::ViewModel<ENVELOPE_COUNT> processor_parameters;

    protected:
        BlockParameters block_parameters;

    private:
        juce::AudioProcessorValueTreeState apvts;
    };
}