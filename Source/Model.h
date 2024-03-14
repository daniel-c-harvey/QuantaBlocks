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

    static std::function<int (const juce::String&)> denominatorValueFromString = 
        [](const juce::String& text) { return TRIGGER_DENOMINATORS[text]; };

    struct Parameters
    {
        float attack_ms;
        float release_ms;
        float phi_curve;
        float gate_portion;
        int gate_num;
        int gate_denom;
        std::vector<float> envelope_gain;
    };
}