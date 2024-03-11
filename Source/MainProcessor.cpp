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
    ), apvts(*this, nullptr, "Parameters", QuantaBlocks::ViewModel::CreateParameterLayout())
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
    processor_parameters.GetParametersFromTree(apvts);
    block_parameters.sample_rate = sampleRate;
    block_parameters.dt = 1000.f / sampleRate;
}

void QuantaBlocks::MainProcessor::processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&)
{
    juce::AudioPlayHead* play_info = this->getPlayHead();
    juce::AudioPlayHead::PositionInfo pos = play_info->getPosition().emplace();
    
    block_parameters.tempo = pos.getBpm().emplace();
    block_parameters.sec_per_beat = 60.f / block_parameters.tempo;
    block_parameters.ms_per_beat = block_parameters.sec_per_beat * 1000.f;
    block_parameters.pulse_per_beat = processor_parameters.SyncDenominator() / 4 * processor_parameters.SyncNumerator(); // TODO replace the 4 with the host tempo denominator
    block_parameters.ms_per_pulse = block_parameters.ms_per_beat / block_parameters.pulse_per_beat;

    float pulse_pos = pos. * block_parameters.pulse_per_beat;
    hold_ms = hold_p * block_parameters.ms_per_beat / block_parameters.pulse_per_beat;
    env_scalar = 0;
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