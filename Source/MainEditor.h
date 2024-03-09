/*
  ==============================================================================

    EnvelopeGateEditor.h
    Created: 8 Mar 2024 11:15:06am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MainProcessor.h"
#include "ViewModel.h"

class EnvelopeGateEditor : public juce::AudioProcessorEditor
{
public:
    EnvelopeGateEditor(EnvelopeGateProcessor&);

    void paint(juce::Graphics&) override;
    void resized() override;

protected:
    EnvelopeGateProcessor& processor;
    QuantaBlocksViewModel model;
};