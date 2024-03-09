/*
  ==============================================================================

    EnvelopeGateProcessor.cpp
    Created: 8 Mar 2024 10:49:49am
    Author:  dharvey

  ==============================================================================
*/

#include "MainProcessor.h"

QuantaBlocksProcessor::QuantaBlocksProcessor()
    : AudioProcessor (juce::AudioProcessor::BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    )
{
}

QuantaBlocksProcessor::~QuantaBlocksProcessor()
{
}

void QuantaBlocksProcessor::processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout QuantaBlocksProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "attack",
        "Attack",
        juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 5.f, false),
        10.f,
        "Attack (ms)"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "release",
        "Release",
        juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 5.f, false),
        10.f,
        "Release(ms)"
        ));

    return layout;
}