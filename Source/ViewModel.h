/*
  ==============================================================================

    EnvelopeGateEditorViewModel.h
    Created: 9 Mar 2024 5:01:52am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace QuantaBlocks
{
    const static struct {
        const juce::String ATTACK = "attack";
        const juce::String RELEASE = "release";
        const juce::String CURVE = "curve";
        const juce::String GATE = "gate";
        const juce::String NUM = "sync_numerator";
        const juce::String DENOM = "sync_denominator";
        const juce::String GAIN = "gain";
    } PARAM_NAMES;

    struct Parameters
    {
        float attack_ms;
        float release_ms;
        float phi_curve;
        float gate_portion;
        int gate_num;
        int gate_denom;
        std::vector<float> env_gain;
    };

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
        QuantaBlocks::Parameters* LoadFromTree(juce::AudioProcessorValueTreeState&);
    
    protected:    
        Parameters parameters;
    };
}