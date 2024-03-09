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

class QuantaBlocksEditor : public juce::AudioProcessorEditor
{
public:
    QuantaBlocksEditor(QuantaBlocksProcessor&);

    void paint(juce::Graphics&) override;
    void resized() override;

protected:
    QuantaBlocksProcessor& processor;
    QuantaBlocksViewModel model;
};