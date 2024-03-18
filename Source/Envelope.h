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

namespace QuantaBlocks
{
    // simple attack -> release countour (rise & fall time)
    // phi is an exponential coefficient which controls the snappiness of the envelope
    struct EnvelopeParameters
    {
        std::shared_ptr<float> attack_ms;
        std::shared_ptr<float> release_ms;
        std::shared_ptr<float> phi_curve;

        void virtual operator=(const EnvelopeParameters&);
    };

    struct AHREnvelopeParameters : EnvelopeParameters
    {
        std::shared_ptr<float> hold_ms;

        void virtual operator=(const AHREnvelopeParameters&);
    };

    template <typename TEnvelopeParams>
    class Envelope
    {
    public:
        Envelope(const TEnvelopeParams&);
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
        AHREnvelope(const AHREnvelopeParameters&);
        ~AHREnvelope();

        //======================================================================
        virtual float processCountour(float t_env) override;
    };

    //**************************************************************************

    template<typename TEnvelopeParams>
    inline Envelope<TEnvelopeParams>::Envelope(const TEnvelopeParams& p)
    {
        parameters = p;
    }
    template<typename TEnvelopeParams>
    inline Envelope<TEnvelopeParams>::~Envelope()
    {
        // empty
    }
}