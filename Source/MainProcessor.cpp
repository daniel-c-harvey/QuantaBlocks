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
}

QuantaBlocks::MainProcessor::~MainProcessor()
{
}

void QuantaBlocks::MainProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    processor_parameters.LoadFromTree(apvts);
}

void QuantaBlocks::MainProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    processor_parameters.LoadFromTree(apvts);
    auto time_parameters = getHostTimeInfo();
    if (time_parameters.has_value())
    {    
        juce::ScopedNoDenormals noDenormals;
        
        auto totalNumInputChannels = getTotalNumInputChannels();
        jassert(totalNumInputChannels == 2);

        BlockParameters block_parameters{ getBlockSize(), getSampleRate() };
        time_parameters->blockSetup(processor_parameters.SyncNumerator(),
                                    processor_parameters.SyncDenominator(),
                                    processor_parameters.Gate());
        envelope.prepareBlock();

        float env_scalar;
        for (int sample_index = 0; sample_index < block_parameters.block_length; ++sample_index)
        {
            env_scalar = envelope.processSample(ENVELOPE_COUNT, 
                                                processor_parameters.getParameterModel(), 
                                                block_parameters,
                                                time_parameters.value());

            for (int channel_index = 0; channel_index < totalNumInputChannels; ++channel_index)
            {
                auto* sample = buffer.getWritePointer(channel_index, sample_index);
                *sample = *sample * env_scalar;
            }

            jassert(env_scalar >= 0.f && env_scalar <= 1.f);

            // TESTING ONLY
            apvts.getParameter(QuantaBlocks::PARAMETER_NAMES::OUTPUT)->setValueNotifyingHost(env_scalar);
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
        processor_parameters.LoadFromTree(apvts);
    }
}

std::optional<QuantaBlocks::TimeParameters> QuantaBlocks::MainProcessor::getHostTimeInfo()
{
    auto time_params = std::optional<QuantaBlocks::TimeParameters>();

    juce::AudioPlayHead* play_info = this->getPlayHead();

    auto pos = play_info->getPosition();
    if (!pos) return time_params;
        
    bool is_playing = pos->getIsPlaying();
    if (!is_playing) return time_params;

    auto beat_position = pos->getPpqPosition();
    if (!beat_position) return time_params;

    auto bpm = pos->getBpm();
    if (!bpm || *bpm <= 0) return time_params;

    auto time_signature = pos->getTimeSignature();
    if (!time_signature) return time_params;

    time_params.emplace(TimeParameters(*bpm, time_signature->denominator, *beat_position));

    return time_params;
}