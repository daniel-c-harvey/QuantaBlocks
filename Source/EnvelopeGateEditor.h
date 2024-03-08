/*
  ==============================================================================

    EnvelopeGateEditor.h
    Created: 8 Mar 2024 11:15:06am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EnvelopeGateEditor : public juce::Component
{
public:
    EnvelopeGateEditor(int sizeX, int sizeY);

    int getSizeX();
    int getSizeY();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    int sizeX;
    int sizeY;
};