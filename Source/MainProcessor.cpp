/*
  ==============================================================================

    EnvelopeGateProcessor.cpp
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#include "MainProcessor.h"


QuantaBlocks::MainProcessor::MainProcessor()
    : AudioProcessor(juce::AudioProcessor::BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    ), apvts(*this, nullptr, "Parameters", QuantaBlocks::ViewModel<ENVELOPE_COUNT>::CreateParameterLayout())
{
    block_parameters.block_length = 0;
    block_parameters.sample_rate = 0.f;
    block_parameters.dt = 0.f;
    block_parameters.sec_per_beat = 0.f;
    block_parameters.ms_per_beat = 0.f;
    block_parameters.pulse_per_beat = 0.f;
    block_parameters.ms_per_pulse = 0.f;
    block_parameters.tempo = 0.f;
}

QuantaBlocks::MainProcessor::~MainProcessor()
{
}

void QuantaBlocks::MainProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    processor_parameters.LoadFromTree(apvts);
    block_parameters.sample_rate = sampleRate;
    block_parameters.dt = 1000.f / sampleRate;
    block_parameters.block_length = samplesPerBlock;
}

void QuantaBlocks::MainProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& )
{
    if (getHostTimeInfo())
    {    
        juce::ScopedNoDenormals noDenormals;
        
        auto totalNumInputChannels = getTotalNumInputChannels();
        jassert(totalNumInputChannels == 2);

        block_parameters.sec_per_beat = 60.f / block_parameters.tempo;
        block_parameters.ms_per_beat = block_parameters.sec_per_beat * 1000.f;
        block_parameters.pulse_per_beat = processor_parameters.SyncDenominator() / 
                                          block_parameters.timesignature_denominator *
                                          processor_parameters.SyncNumerator();
        block_parameters.ms_per_pulse = block_parameters.ms_per_beat / 
                                        block_parameters.pulse_per_beat;
        float pulse_pos = block_parameters.pulse_position * 
                          block_parameters.pulse_per_beat;
        float gate_ms = processor_parameters.Gate() * block_parameters.ms_per_beat / 
                                                      block_parameters.pulse_per_beat;

        float env_scalar = 1.f;
        for (int sample_index = 0; sample_index < block_parameters.block_length; ++sample_index)
        {
            float t_pulse = block_parameters.dt / block_parameters.ms_per_pulse;
            float env_groupstart_pos = (pulse_pos + t_pulse) / ENVELOPE_COUNT * ENVELOPE_COUNT;
            float env_number = static_cast<int>(pulse_pos + t_pulse) % ENVELOPE_COUNT;
            float env_start_pos = (env_groupstart_pos + env_number);

            for (int channel_index = 0; channel_index < totalNumInputChannels; ++channel_index)
            {
                auto* sample = buffer.getWritePointer(channel_index, sample_index);
                *sample = *sample * env_scalar;
            }
        }
    }
}



void QuantaBlocks::MainProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void QuantaBlocks::MainProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.state = tree;
    }
}

bool QuantaBlocks::MainProcessor::getHostTimeInfo()
{
    juce::AudioPlayHead* play_info = this->getPlayHead();
        
    auto pos = play_info->getPosition();
    if (!pos) return false;
        
    auto beat_position = pos->getPpqPosition();
    if (!beat_position) return false;
    block_parameters.pulse_position = *beat_position;

    auto bpm = pos->getBpm();
    if (!bpm) return false;
    block_parameters.tempo = *bpm;

    auto time_signature = pos->getTimeSignature();
    if (!time_signature) return false;
    block_parameters.timesignature_denominator = time_signature->denominator;

    return true;
}