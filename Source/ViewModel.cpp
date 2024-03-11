/*
  ==============================================================================

    EnvelopeGateEditorViewModel.cpp
    Created: 9 Mar 2024 5:01:52am
    Author:  dharvey

  ==============================================================================
*/

#include "ViewModel.h"
#include <string>

template <int ENVELOPE_COUNT>
QuantaBlocks::ViewModel<ENVELOPE_COUNT>::ViewModel()
{
    parameters.attack_ms = 0.f;
    parameters.release_ms = 0.f;
    parameters.gate_portion = 0.f;
    parameters.phi_curve = 1.f;
    parameters.env_gain = std::vector<float>((size_t)ENVELOPE_COUNT);
}

template <int ENVELOPE_COUNT>
QuantaBlocks::ViewModel<ENVELOPE_COUNT>::~ViewModel()
{
}

template <int ENVELOPE_COUNT>
float QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Attack()
{
    return parameters.attack_ms;
}

template <int ENVELOPE_COUNT>
void QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Attack(float attack)
{
    parameters.attack_ms = attack;
}

template <int ENVELOPE_COUNT>
float QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Release()
{
    return parameters.release_ms;
}

template <int ENVELOPE_COUNT>
void QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Release(float release)
{
    parameters.release_ms = release;
}

template <int ENVELOPE_COUNT>
float QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Curve()
{
    return parameters.phi_curve;
}

template <int ENVELOPE_COUNT>
void QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Curve(float curve)
{
    parameters.phi_curve = curve;
}

template <int ENVELOPE_COUNT>
float QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Gate()
{
    return parameters.gate_portion;
}

template <int ENVELOPE_COUNT>
void QuantaBlocks::ViewModel<ENVELOPE_COUNT>::Gate(float gate)
{
    parameters.gate_portion = gate;
}

template <int ENVELOPE_COUNT>
int QuantaBlocks::ViewModel<ENVELOPE_COUNT>::SyncNumerator()
{
    return parameters.gate_num;
}

template <int ENVELOPE_COUNT>
void QuantaBlocks::ViewModel<ENVELOPE_COUNT>::SyncNumerator(int numerator)
{
    parameters.gate_num = numerator;
}

template <int ENVELOPE_COUNT>
int QuantaBlocks::ViewModel<ENVELOPE_COUNT>::SyncDenominator()
{
    return parameters.gate_denom;
}

template <int ENVELOPE_COUNT>
void QuantaBlocks::ViewModel<ENVELOPE_COUNT>::SyncDenominator(int denominator)
{
    parameters.gate_denom = denominator;
}

template <int ENVELOPE_COUNT>
float QuantaBlocks::ViewModel<ENVELOPE_COUNT>::EnvGain(int envelope_index)
{
    if (envelope_index >= 0 && envelope_index < parameters.env_gain.size()) {
        return parameters.env_gain[envelope_index];
    }
    std::string error_message = "Invalid Index for envelope: " + std::to_string(envelope_index);
    throw new std::exception(error_message.c_str());
}

template <int ENVELOPE_COUNT>
void QuantaBlocks::ViewModel<ENVELOPE_COUNT>::EnvGain(int envelope_index, float gain)
{
    if (envelope_index >= 0 && envelope_index < parameters.env_gain.size()) {
        parameters.env_gain[envelope_index] = gain;
    }
    else
    {
        std::string error_message = "Invalid Index for envelope: " + std::to_string(envelope_index);
        throw new std::exception(error_message.c_str());
    }
}

template <int ENVELOPE_COUNT>
juce::AudioProcessorValueTreeState::ParameterLayout QuantaBlocks::ViewModel<ENVELOPE_COUNT>::CreateParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        QuantaBlocks::PARAM_NAMES.ATTACK,
        "Attack",
        juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 0.5f, false),
        10.f,
        "Attack (ms)"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        QuantaBlocks::PARAM_NAMES.RELEASE,
        "Release",
        juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 0.5f, false),
        10.f,
        "Release (ms)"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        QuantaBlocks::PARAM_NAMES.CURVE,
        "Curve",
        juce::NormalisableRange<float>(0.1f, 10.f, 1.f, 0.8f, true),
        1.f,
        "Curve (φ)"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        QuantaBlocks::PARAM_NAMES.GATE,
        "Gate",
        juce::NormalisableRange<float>(0.f, 1.f, 0.12625f, 1.f, false),
        0.5f,
        "Gate Portion"
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        QuantaBlocks::PARAM_NAMES.GAIN,
        "Gain1",
        juce::NormalisableRange<float>(0.f, 1.f, 0.12625f, 1.f, false),
        1.f,
        "Envelope Gain 1"
        ));

    return layout;
}


template <int ENVELOPE_COUNT>
QuantaBlocks::Parameters* QuantaBlocks::ViewModel<ENVELOPE_COUNT>::LoadFromTree(juce::AudioProcessorValueTreeState& apvts)
{
    parameters.attack_ms = apvts.getRawParameterValue(QuantaBlocks::PARAM_NAMES.ATTACK)->load();
    parameters.release_ms = apvts.getRawParameterValue(QuantaBlocks::PARAM_NAMES.RELEASE)->load();
    parameters.phi_curve = apvts.getRawParameterValue(QuantaBlocks::PARAM_NAMES.CURVE)->load();
    parameters.gate_portion = apvts.getRawParameterValue(QuantaBlocks::PARAM_NAMES.GATE)->load();
    for (float& gain : parameters.env_gain)
    {
        gain = apvts.getRawParameterValue(QuantaBlocks::PARAM_NAMES.GAIN)->load();
    }

    return &parameters;
}
