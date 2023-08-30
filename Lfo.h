/*
  ==============================================================================

    Lfo.h
    Created: 26 Jul 2023 6:25:44pm
    Author:  37060

  ==============================================================================
*/

#pragma once

class Lfo {
public:
    void setAmplitude(float amplitude);
    void setFrequency(float freq);
    void initialise(float sampleRate);
    float renderSample();
private:
    void setSampleRate(float sampleRate);
    float sampleRate;
    float phase;
    float increment;
    float amplitude;
    const double pi = 3.14159265358979323846;
};
