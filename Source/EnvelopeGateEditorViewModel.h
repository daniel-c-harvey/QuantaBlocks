/*
  ==============================================================================

    EnvelopeGateEditorViewModel.h
    Created: 9 Mar 2024 5:01:52am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class QuantaBlocksViewModel
{
public:
    QuantaBlocksViewModel();

    float getAttack();
    void setAttack(float);

    float getRelease();
    void setRelease(float);
    
    float getCurve();
    void setCurve(float);
    
    float getHold();
    void setHold(float);
    
    float getEnvGain();
    void setEnvGain(float);
    
protected:    
    float attack_ms;
    float release_ms;
    float phi_curve;
    float hold_ms;
    float env_gain;
};