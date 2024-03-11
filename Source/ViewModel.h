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
    struct Parameters
    {
        float attack_ms;
        float release_ms;
        float phi_curve;
        float gate_portion;
        float env_gain;
    };

    class ViewModel
    {
    public:
        ViewModel();

        // Accessors & Modifiers
        float Attack();
        void Attack(float);

        float Release();
        void Release(float);
    
        float Curve();
        void Curve(float);
    
        float Gate();
        void Gate(float);
    
        float EnvGain();
        void EnvGain(float);

        static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    protected:    
        Parameters parameters;
    };
}