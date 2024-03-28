/*
  ==============================================================================

    Model.h
    Created: 12 Mar 2024 6:27:51am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#define NAMEOF(name) #name

#include <JuceHeader.h>
#include "Enumeration.h"

namespace QuantaBlocks
{
    constexpr static struct PARAMETER_NAMES
    {
    private:
        inline static juce::String GAIN_PREFIX{ "gain" };
    public:
        inline static juce::String ATTACK { "attack" };
        inline static juce::String RELEASE{ "release" };
        inline static juce::String CURVE{ "curve" };
        inline static juce::String GATE{ "gate" };
        inline static juce::String NUM{ "sync_numerator" };
        inline static juce::String DENOM{ "sync_denominator" };
        inline static juce::String OUTPUT{ "output" };
        static juce::String GAIN(int envelope_number)
        {
            return GAIN_PREFIX + std::to_string(envelope_number);
        }
    } PARAMETER_NAMES;


    class SyncDenominatorChoice : public Enumeration<SyncDenominatorChoice>
    {
    public:
        juce::String label;
        int denominator_value;

        static SyncDenominatorChoice C01;
        static SyncDenominatorChoice C02;
        static SyncDenominatorChoice C04;
        static SyncDenominatorChoice C08;
        static SyncDenominatorChoice C12;
        static SyncDenominatorChoice C16;
        static SyncDenominatorChoice C32;

        SyncDenominatorChoice(const int& id, const std::string& name, const juce::String& label, const int& value)
            : Enumeration<SyncDenominatorChoice>(id, name), label{label}, denominator_value{value} {}
    
        static SyncDenominatorChoice* getByLabel(const juce::String& label);
    };

    struct ModelParameters
    {
        std::shared_ptr<float> attack_ms;
        std::shared_ptr<float> release_ms;
        std::shared_ptr<float> phi_curve; // add alpha beta variants for attack and release
        std::shared_ptr<float> gate_portion;
        std::shared_ptr<float> gate_ms;
        std::shared_ptr<int> gate_num;
        std::shared_ptr<int> gate_denom;
        std::vector<float> envelope_gain;
    };
}