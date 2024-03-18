/*
  ==============================================================================

    Envelope.cpp
    Created: 18 Mar 2024 6:30:13am
    Author:  dharvey

  ==============================================================================
*/

#include <cmath>
#include "Envelope.h"


void QuantaBlocks::EnvelopeParameters::operator=(const EnvelopeParameters& other)
{
    attack_ms = other.attack_ms;
    release_ms = other.release_ms;
    phi_curve = other.phi_curve;
}

void QuantaBlocks::AHREnvelopeParameters::operator=(const AHREnvelopeParameters& other)
{
    EnvelopeParameters::operator=(other);
    hold_ms = other.hold_ms;
}

QuantaBlocks::AHREnvelope::AHREnvelope(const AHREnvelopeParameters& params) : Envelope<AHREnvelopeParameters>(params) {}

QuantaBlocks::AHREnvelope::~AHREnvelope()
{
}

float QuantaBlocks::AHREnvelope::processCountour(float t_env)
{
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
        return 1 - std::powf((t_env - *parameters.attack_ms - *parameters.hold_ms) / *parameters.release_ms, *parameters.phi_curve);
    }
    else {
        stage = "End";
        return 0.f; // close the contour out
    }
}
