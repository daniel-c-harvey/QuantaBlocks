/*
  ==============================================================================

    Model.h
    Created: 12 Mar 2024 6:27:51am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace QuantaBlocks
{
    const static struct PARAMETER_NAMES
    {
    private:
        static const juce::String _GAIN;
    public:
        static const juce::String ATTACK;
        static const juce::String RELEASE;
        static const juce::String CURVE;
        static const juce::String GATE;
        static const juce::String NUM;
        static const juce::String DENOM;
        static juce::String GAIN(int envelope_number);
        static const juce::String OUTPUT;
    };

    // denominations of musical pulse that are actually useful (feel free to add or take away if you disagree)
    static std::map<juce::String, int> TRIGGER_DENOMINATORS
    {
        { "1",   1 },
        { "2",   2 },
        { "4",   4 },
        { "8",   8 },
        { "12", 12 },
        { "16", 16 },
        { "24", 24 },
        { "32", 32 },
        { "64", 64 }
    };

    static int denominatorValue(const juce::String& text)
    {
        return TRIGGER_DENOMINATORS[text]; // todo I don't think the string matching is working since the instances are different
    }


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