/*
  ==============================================================================

    EnvelopeGateEditorViewModel.cpp
    Created: 9 Mar 2024 5:01:52am
    Author:  dharvey

  ==============================================================================
*/

#include "ViewModel.h"

QuantaBlocks::ViewModel::ViewModel()
{
    parameters.attack_ms = 0.f;
    parameters.release_ms = 0.f;
    parameters.gate_portion = 0.f;
    parameters.phi_curve = 1.f;
    parameters.env_gain = 1.f;
}

float QuantaBlocks::ViewModel::Attack()
{
    return parameters.attack_ms;
}

void QuantaBlocks::ViewModel::Attack(float attack)
{
    parameters.attack_ms = attack;
}

float QuantaBlocks::ViewModel::Release()
{
    return parameters.release_ms;
}

void QuantaBlocks::ViewModel::Release(float release)
{
    parameters.release_ms = release;
}

float QuantaBlocks::ViewModel::Curve()
{
    return parameters.phi_curve;
}

void QuantaBlocks::ViewModel::Curve(float curve)
{
    parameters.phi_curve = curve;
}

float QuantaBlocks::ViewModel::Gate()
{
    return parameters.gate_portion;
}

void QuantaBlocks::ViewModel::Gate(float gate)
{
    parameters.gate_portion = gate;
}

float QuantaBlocks::ViewModel::EnvGain()
{
    return parameters.env_gain;
}

void QuantaBlocks::ViewModel::EnvGain(float gain)
{
    parameters.env_gain = gain;
}

juce::AudioProcessorValueTreeState::ParameterLayout QuantaBlocks::ViewModel::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "attack",
        "Attack",
        juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 0.5f, false),
        10.f,
        "Attack (ms)"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "release",
        "Release",
        juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 0.5f, false),
        10.f,
        "Release (ms)"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "curve",
        "Curve",
        juce::NormalisableRange<float>(0.1f, 10.f, 1.f, 0.8f, true),
        1.f,
        "Curve (φ)"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "gate",
        "Gate",
        juce::NormalisableRange<float>(0.f, 1.f, 0.12625f, 1.f, false),
        0.5f,
        "Gate Portion"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "gain1",
        "Gain1",
        juce::NormalisableRange<float>(0.f, 1.f, 0.12625f, 1.f, false),
        1.f,
        "Envelope Gain 1"
        ));

    return layout;
}