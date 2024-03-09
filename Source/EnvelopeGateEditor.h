/*
  ==============================================================================

    EnvelopeGateEditor.h
    Created: 8 Mar 2024 11:15:06am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EnvelopeGateProcessor.h"

class EnvelopeGateEditor : public juce::AudioProcessorEditor
{
public:
    EnvelopeGateEditor(EnvelopeGateProcessor&);

    int getSizeX();
    int getSizeY();

    void paint(juce::Graphics&) override;
    void resized() override;

protected:
    EnvelopeGateProcessor& processor;

private:
    int sizeX;
    int sizeY;
};