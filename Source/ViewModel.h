/*
  ==============================================================================

    EnvelopeGateEditorViewModel.h
    Created: 9 Mar 2024 5:01:52am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string>
#include "Model.h"

namespace QuantaBlocks
{

    template <int ENVELOPE_COUNT>
    class ViewModel
    {
    public:
        ViewModel();
        ~ViewModel();

        // Accessors & Modifiers
        float Attack();
        void Attack(float);

        float Release();
        void Release(float);
        
        float Curve();
        void Curve(float);
        
        float Gate();
        void Gate(float);

        int SyncNumerator();
        void SyncNumerator(int);
        
        int SyncDenominator();
        void SyncDenominator(int);
        
        float EnvGain(int);
        void EnvGain(int, float);

        static juce::AudioProcessorValueTreeState::ParameterLayout CreateParameterLayout();
        Parameters* LoadFromTree(juce::AudioProcessorValueTreeState&);
    
    protected:    
        Parameters parameters;
    };

    template <int ENVELOPE_COUNT>
    inline ViewModel<ENVELOPE_COUNT>::ViewModel()
    {
        parameters.attack_ms = 0.f;
        parameters.release_ms = 0.f;
        parameters.gate_portion = 0.f;
        parameters.phi_curve = 1.f;
        parameters.envelope_gain = std::vector<float>(ENVELOPE_COUNT);
    }

    template <int ENVELOPE_COUNT>
    ViewModel<ENVELOPE_COUNT>::~ViewModel()
    {
    }

    template <int ENVELOPE_COUNT>
    float ViewModel<ENVELOPE_COUNT>::Attack()
    {
        return parameters.attack_ms;
    }

    template <int ENVELOPE_COUNT>
    void ViewModel<ENVELOPE_COUNT>::Attack(float attack)
    {
        parameters.attack_ms = attack;
    }

    template <int ENVELOPE_COUNT>
    float ViewModel<ENVELOPE_COUNT>::Release()
    {
        return parameters.release_ms;
    }

    template <int ENVELOPE_COUNT>
    void ViewModel<ENVELOPE_COUNT>::Release(float release)
    {
        parameters.release_ms = release;
    }

    template <int ENVELOPE_COUNT>
    float ViewModel<ENVELOPE_COUNT>::Curve()
    {
        return parameters.phi_curve;
    }

    template <int ENVELOPE_COUNT>
    void ViewModel<ENVELOPE_COUNT>::Curve(float curve)
    {
        parameters.phi_curve = curve;
    }

    template <int ENVELOPE_COUNT>
    float ViewModel<ENVELOPE_COUNT>::Gate()
    {
        return parameters.gate_portion;
    }

    template <int ENVELOPE_COUNT>
    void ViewModel<ENVELOPE_COUNT>::Gate(float gate)
    {
        parameters.gate_portion = gate;
    }

    template <int ENVELOPE_COUNT>
    int ViewModel<ENVELOPE_COUNT>::SyncNumerator()
    {
        return parameters.gate_num;
    }

    template <int ENVELOPE_COUNT>
    void ViewModel<ENVELOPE_COUNT>::SyncNumerator(int numerator)
    {
        parameters.gate_num = numerator;
    }

    template <int ENVELOPE_COUNT>
    int ViewModel<ENVELOPE_COUNT>::SyncDenominator()
    {
        return parameters.gate_denom;
    }

    template <int ENVELOPE_COUNT>
    void ViewModel<ENVELOPE_COUNT>::SyncDenominator(int denominator)
    {
        parameters.gate_denom = denominator;
    }

    template <int ENVELOPE_COUNT>
    float ViewModel<ENVELOPE_COUNT>::EnvGain(int envelope_index)
    {
        if (envelope_index >= 0 && envelope_index < parameters.envelope_gain.size()) {
            return parameters.envelope_gain[envelope_index];
        }
        std::string error_message = "Invalid Index for envelope: " + std::to_string(envelope_index);
        throw new std::exception(error_message.c_str());
    }

    template <int ENVELOPE_COUNT>
    void ViewModel<ENVELOPE_COUNT>::EnvGain(int envelope_index, float gain)
    {
        if (envelope_index >= 0 && envelope_index < parameters.envelope_gain.size()) {
            parameters.envelope_gain[envelope_index] = gain;
        }
        else
        {
            std::string error_message = "Invalid Index for envelope: " + std::to_string(envelope_index);
            throw new std::exception(error_message.c_str());
        }
    }

    template <int ENVELOPE_COUNT>
    juce::AudioProcessorValueTreeState::ParameterLayout ViewModel<ENVELOPE_COUNT>::CreateParameterLayout()
    {
        juce::AudioProcessorValueTreeState::ParameterLayout layout;

        layout.add(std::make_unique<juce::AudioParameterFloat>(
            PARAMETER_NAMES::ATTACK,
            "Attack",
            juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 0.5f, false),
            10.f,
            "Attack (ms)"
            ));

        layout.add(std::make_unique<juce::AudioParameterFloat>(
            PARAMETER_NAMES::RELEASE,
            "Release",
            juce::NormalisableRange<float>(0.f, 2000.f, 1.f, 0.5f, false),
            10.f,
            "Release (ms)"
            ));

        layout.add(std::make_unique<juce::AudioParameterFloat>(
            PARAMETER_NAMES::CURVE,
            "Curve",
            juce::NormalisableRange<float>(0.1f, 10.f, 0.1f, 0.3f, false),
            1.f,
            juce::CharPointer_UTF8("Curve (φ)")
            ));

        layout.add(std::make_unique<juce::AudioParameterFloat>(
            PARAMETER_NAMES::GATE,
            "Gate",
            juce::NormalisableRange<float>(0.f, 1.f, 0.03125, 1.f, false),
            0.5f,
            "Gate Portion"
            ));

        for (int envelope_number = 1; envelope_number <= ENVELOPE_COUNT; ++envelope_number)
        {
            auto env_number = std::to_string(envelope_number);
            layout.add(std::make_unique<juce::AudioParameterFloat>(
                PARAMETER_NAMES::GAIN(envelope_number),
                "Gain" + env_number,
                juce::NormalisableRange<float>(0.f, 1.f, 0.03125, 1.f, false),
                1.f,
                "Envelope Gain " + env_number
                ));
        }

        return layout;
    }

    template <int ENVELOPE_COUNT>
    Parameters* ViewModel<ENVELOPE_COUNT>::LoadFromTree(juce::AudioProcessorValueTreeState& apvts)
    {
        parameters.attack_ms = apvts.getRawParameterValue(PARAMETER_NAMES::ATTACK)->load();
        parameters.release_ms = apvts.getRawParameterValue(PARAMETER_NAMES::RELEASE)->load();
        parameters.phi_curve = apvts.getRawParameterValue(PARAMETER_NAMES::CURVE)->load();
        parameters.gate_portion = apvts.getRawParameterValue(PARAMETER_NAMES::GATE)->load();
        for (int envelope_index = 0; envelope_index < ENVELOPE_COUNT; ++envelope_index)
        {
            parameters.envelope_gain[envelope_index] = apvts.getRawParameterValue(PARAMETER_NAMES::GAIN(envelope_index + 1))->load();
        }

        return &parameters;
    }
}
