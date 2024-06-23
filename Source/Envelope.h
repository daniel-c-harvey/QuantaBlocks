/*
  ==============================================================================

    Envelope.h
    Created: 18 Mar 2024 6:30:13am
    Author:  dharvey

  ==============================================================================
*/

#pragma once
#include <string>
#include <memory>
#include "Model.h"

namespace QuantaBlocks
{
    // simple attack -> release countour (rise & fall time)
    // phi is an exponential coefficient which controls the snappiness of the envelope
    struct EnvelopeParameters
    {
        float* attack_ms;
        float* release_ms;
        float* phi_curve;

        EnvelopeParameters(const ModelParameters&);
        ~EnvelopeParameters();

        void virtual operator=(const EnvelopeParameters&);
    };

    struct AHREnvelopeParameters : EnvelopeParameters
    {
        AHREnvelopeParameters(const ModelParameters&);
        AHREnvelopeParameters(const AHREnvelopeParameters&);
        ~AHREnvelopeParameters();
        
        float* hold_ms;

        void virtual operator=(const AHREnvelopeParameters&);
    };

    template <typename TEnvelopeParams>
    class Envelope
    {
    public:
        Envelope(const ModelParameters&);
        ~Envelope();

        //======================================================================
        virtual float processCountour(float t_env) = 0;
        std::string stage;

    protected:
        TEnvelopeParams parameters;
    };

    class AHREnvelope : public Envelope<AHREnvelopeParameters>
    {
    public:
        AHREnvelope(const ModelParameters&);
        ~AHREnvelope();

        //======================================================================
        virtual float processCountour(float t_env) override;
    };

    //**************************************************************************

    template<typename TEnvelopeParams>
    inline Envelope<TEnvelopeParams>::Envelope(const ModelParameters& p)
        : parameters(p)
    { /* empty */ }

    template<typename TEnvelopeParams>
    inline Envelope<TEnvelopeParams>::~Envelope()
    { /* empty */ }
}