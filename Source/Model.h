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

namespace QuantaBlocks
{
    const static struct PARAMETER_NAMES
    {
    private:
        static const juce::String _GAIN;
    public:
        static constexpr juce::String ATTACK;
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

    template <typename TEnum>
    class Enumeration
    {
    public:
        int id;
        std::string name;

        std::shared_ptr<std::set<TEnum>> getAll()
        {
            //if () // oh boy
        }
    protected:
        Enumeration(int id, std::string name)
        {
            this->id = id;
            this->name = name;
        }

        inline static std::set<TEnum*> enum_set{};
        inline static std::unordered_map<int, TEnum*> enum_map{};
    };

    template <class TEnum>
    class _SyncDenominatorChoices : Enumeration<TEnum>
    {
    private:
        _SyncDenominatorChoices(const int& id, const std::string& name, const juce::String& label, const int& value)
            : Enumeration<TEnum>(id, name)
        {
            Enumeration<TEnum>::enum_set.insert(this);
            enum_map.insert_or_assign(this->id, this);
        }
    public:
        constexpr static TEnum C01{ 1, NAMEOF(C01) };
        constexpr static TEnum C02{ 2, NAMEOF(C02) };
    };

    class SyncDenominatorChoices : public _SyncDenominatorChoices<SyncDenominatorChoices> {};

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