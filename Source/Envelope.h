/*
  ==============================================================================

    Envelope.h
    Created: 18 Mar 2024 2:54:04am
    Author:  dharvey

  ==============================================================================
*/

#pragma once

#include "Model.h"

namespace QuantaBlocks
{
    struct BlockParameters
    {
        int block_length;
        double sample_rate;
        float dt;

        BlockParameters();
        BlockParameters(int, double);
        void update(int, double);
    private:
        void init(int, double);
    };

    struct TimeParameters
    {
        float sec_per_beat;
        float ms_per_beat;
        float pulse_per_beat;
        float ms_per_pulse;
        float pulse_position;

        float gate_ms;

        double tempo;
        int timesignature_denominator;
        double beat_position;

        TimeParameters(double, int, double);

        //===========================================================
        void update(double, int, double);
        void blockSetup(int, int, float);

    private:
        void init(double, int, double);
    };

    class Envelope
    {
    public:
        Envelope();
        ~Envelope();

        //===========================================================
        void prepareBlock();
        void processSample(int, std::unique_ptr<Parameters>, const BlockParameters&, const TimeParameters&);

    private:
        
        float t_ms;
    };
}