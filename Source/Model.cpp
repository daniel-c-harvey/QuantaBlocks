/*
  ==============================================================================

    Model.cpp
    Created: 12 Mar 2024 6:27:51am
    Author:  dharvey

  ==============================================================================
*/

#include "Model.h"

const juce::String QuantaBlocks::PARAMETER_NAMES::ATTACK{ "attack" };
const juce::String QuantaBlocks::PARAMETER_NAMES::RELEASE{ "release" };
const juce::String QuantaBlocks::PARAMETER_NAMES::CURVE{ "curve" };
const juce::String QuantaBlocks::PARAMETER_NAMES::GATE{ "gate" };
const juce::String QuantaBlocks::PARAMETER_NAMES::NUM{ "sync_numerator" };
const juce::String QuantaBlocks::PARAMETER_NAMES::DENOM{ "sync_denominator" };
const juce::String QuantaBlocks::PARAMETER_NAMES::_GAIN{ "gain" };

juce::String QuantaBlocks::PARAMETER_NAMES::GAIN(int envelope_number)
{
    return _GAIN + std::to_string(envelope_number);
}