/*
  ==============================================================================

    EnvelopeGateEditorViewModel.cpp
    Created: 9 Mar 2024 5:01:52am
    Author:  dharvey

  ==============================================================================
*/

#include "ViewModel.h"

QuantaBlocksViewModel::QuantaBlocksViewModel(QuantaBlocksProcessor& p)
    : apvts { p, nullptr, "Parameters", createParameterLayout() }
{
    attack_ms = 0.f;
    release_ms = 0.f;
    hold_ms = 0.f;
    phi_curve = 1.f;
    env_gain = 1.f;
}

float QuantaBlocksViewModel::getAttack()
{
    return attack_ms;
}

void QuantaBlocksViewModel::setAttack(float attack)
{
    attack_ms = attack;
}

float QuantaBlocksViewModel::getRelease()
{
    return release_ms;
}

void QuantaBlocksViewModel::setRelease(float release)
{
    release_ms = release;
}

float QuantaBlocksViewModel::getCurve()
{
    return phi_curve;
}

void QuantaBlocksViewModel::setCurve(float curve)
{
    phi_curve = curve;
}

float QuantaBlocksViewModel::getHold()
{
    return hold_ms;
}

void QuantaBlocksViewModel::setHold(float hold)
{
    hold_ms = hold;
}

float QuantaBlocksViewModel::getEnvGain()
{
    return env_gain;
}

void QuantaBlocksViewModel::setEnvGain(float gain)
{
    env_gain = gain;
}

juce::AudioProcessorValueTreeState::ParameterLayout QuantaBlocksViewModel::createParameterLayout()
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