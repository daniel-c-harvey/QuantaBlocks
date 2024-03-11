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

namespace QuantaBlocks
{
    class MainEditor : public juce::AudioProcessorEditor
    {
    public:
        MainEditor(QuantaBlocks::MainProcessor&);

        void paint(juce::Graphics&) override;
        void resized() override;

    protected:
        QuantaBlocks::MainProcessor& processor;
    };
}