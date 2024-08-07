/*
  ==============================================================================

    Envelope.cpp
    Created: 18 Mar 2024 6:30:13am
    Author:  dharvey

  ==============================================================================
*/

#include <cmath>
#include "Envelope.h"

QuantaBlocks::EnvelopeParameters::EnvelopeParameters(const ModelParameters& parameters)
{
    this->attack_ms = parameters.attack_ms;
    //this->attack_ms = std::make_shared<float>(&parameters.attack_ms);
    this->release_ms = parameters.release_ms;
    this->phi_curve = parameters.phi_curve;
}

QuantaBlocks::EnvelopeParameters::~EnvelopeParameters()
{
}

void QuantaBlocks::EnvelopeParameters::operator=(const EnvelopeParameters& other)
{
    attack_ms = other.attack_ms;
    release_ms = other.release_ms;
    phi_curve = other.phi_curve;
}

QuantaBlocks::AHREnvelopeParameters::AHREnvelopeParameters(const ModelParameters& parameters)
    : QuantaBlocks::EnvelopeParameters::EnvelopeParameters(parameters)
{
    hold_ms = parameters.gate_ms;
}

QuantaBlocks::AHREnvelopeParameters::AHREnvelopeParameters(const AHREnvelopeParameters& other)
    : QuantaBlocks::EnvelopeParameters::EnvelopeParameters(other)
{
    hold_ms = other.hold_ms;
}

QuantaBlocks::AHREnvelopeParameters::~AHREnvelopeParameters()
{
}

void QuantaBlocks::AHREnvelopeParameters::operator=(const AHREnvelopeParameters& other)
{
    EnvelopeParameters::operator=(other);
    hold_ms = other.hold_ms;
}

QuantaBlocks::AHREnvelope::AHREnvelope(const ModelParameters& parameters) 
    : Envelope<AHREnvelopeParameters>(parameters) 
{
}

QuantaBlocks::AHREnvelope::~AHREnvelope()
{
}

float QuantaBlocks::AHREnvelope::processCountour(float t_env)
{
    /*if (t_env < 1.f) {
        return 1.f;
    }*/
    if (t_env < *parameters.attack_ms) {
        stage = "Attack";
        return std::powf(t_env / *parameters.attack_ms, *parameters.phi_curve);
    }
    else if (t_env < *parameters.attack_ms + *parameters.hold_ms)
    {
        stage = "Hold";
        return 1.f; // hold at full range
    }
    else if (t_env < *parameters.attack_ms + *parameters.hold_ms + *parameters.release_ms)
    {
        stage = "Release";
        return 1.f - std::powf((t_env - *parameters.attack_ms - *parameters.hold_ms) / *parameters.release_ms, *parameters.phi_curve);
    }
    else {
        stage = "End";
        return 0.f; // close the contour out
    }
}
