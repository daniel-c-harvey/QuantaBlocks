/*
  ==============================================================================

    Envelope.cpp
    Created: 18 Mar 2024 2:54:04am
    Author:  dharvey

  ==============================================================================
*/

#include "EnvelopeGroupProcessor.h"

QuantaBlocks::BlockParameters::BlockParameters()
{
    block_length = 0;
    sample_rate = 0.f;
    dt = 0.f;
}

QuantaBlocks::BlockParameters::BlockParameters(int block_length, double sample_rate)
{
    init(block_length, sample_rate);
}

void QuantaBlocks::BlockParameters::update(int block_length, double sample_rate)
{
    init(block_length, sample_rate);
}

void QuantaBlocks::BlockParameters::init(int block_length, double sample_rate)
{
    this->block_length = block_length;
    this->sample_rate = sample_rate;
    this->dt = 1000.f / sample_rate;
}

QuantaBlocks::TimeParameters::TimeParameters(double tempo, int timesignature_denominator, double beat_position)
{
    init(tempo, timesignature_denominator, beat_position);

    sec_per_beat = 60.f / tempo;
    ms_per_beat = sec_per_beat * 1000.f;
}

void QuantaBlocks::TimeParameters::blockSetup(int sync_num, int sync_denom, float gate_length)
{
    pulse_per_beat = static_cast<float>(sync_denom) / static_cast<float>(timesignature_denominator) / static_cast<float>(sync_num);
    ms_per_pulse = ms_per_beat / pulse_per_beat;
    pulse_position = beat_position * pulse_per_beat;
}

void QuantaBlocks::TimeParameters::init(double tempo, int timesignature_denominator, double beat_position)
{
    pulse_per_beat = 0.f;
    ms_per_pulse = 0.f;

    this->tempo = tempo;
    this->timesignature_denominator = timesignature_denominator;
    this->beat_position = beat_position;
}

template <typename TEnvelope>
QuantaBlocks::EnvelopeGroupProcessor<TEnvelope>::EnvelopeGroupProcessor(const ModelParameters& parameters)
    : envelope{ std::make_shared<TEnvelope>(TEnvelope(parameters)) }
{
    t_ms = 0.f;
}

template <typename TEnvelope>
QuantaBlocks::EnvelopeGroupProcessor<TEnvelope>::~EnvelopeGroupProcessor()
{
}

template <typename TEnvelope>
void QuantaBlocks::EnvelopeGroupProcessor<TEnvelope>::prepareBlock()
{
    t_ms = 0.f;
}

template <typename TEnvelope>
float QuantaBlocks::EnvelopeGroupProcessor<TEnvelope>::processSample(int envelope_count, 
                                                                     ModelParameters* processor_parameters, 
                                                                     const BlockParameters& block_parameters,
                                                                     const TimeParameters& time_parameters)
{
    float t_pulse = t_ms * block_parameters.dt / time_parameters.ms_per_pulse;

    float env_groupstart_pos = std::floor((time_parameters.pulse_position + t_pulse) / envelope_count) * envelope_count;
    float env_index = static_cast<int>(time_parameters.pulse_position + t_pulse) % envelope_count;
    
    float env_start_pos = (env_groupstart_pos + env_index);

    float t_env = (time_parameters.pulse_position - env_start_pos) * time_parameters.ms_per_pulse + t_ms;

    float env_scalar = processor_parameters->envelope_gain[env_index];

    jassert(env_scalar >= 0);
    jassert(t_env >= 0);
    
    t_ms += block_parameters.dt;

    return env_scalar * envelope->processCountour(t_env); // todo fix read access violation
}

template QuantaBlocks::EnvelopeGroupProcessor<QuantaBlocks::AHREnvelope>;