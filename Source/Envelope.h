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
    class Envelope
    {
    public:
        Envelope();
        ~Envelope();

        void prepareBlock();
    private:
        TimeParameters time_parameters;
    };
}