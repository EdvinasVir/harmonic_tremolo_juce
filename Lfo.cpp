/*
  ==============================================================================

	Lfo.cpp
	Created: 26 Jul 2023 6:25:44pm
	Author:  37060

  ==============================================================================
*/

#include "Lfo.h"
#include <cmath>

void Lfo::setSampleRate(float sampleRate) {
	this->sampleRate = sampleRate;
}

void Lfo::setAmplitude(float amplitude) {
	this->amplitude = amplitude;
}

void Lfo::setFrequency(float freq) {
	this->increment = freq / sampleRate;
}

void Lfo::initialise(float sampleRate) {
	setSampleRate(sampleRate);
	this->phase = 0.0f;
	this->increment = 0.0f;
	this->amplitude = 1.0f;
}

float Lfo::renderSample() {
	float output = (((float)std::sin(phase * 2.0f * pi) * 0.5f) * amplitude) + 0.5f; // argument is in radians, output is 0 - 1
	phase += increment;
	if (phase > 1.0f) {
		phase -= 1.0f;
	}
	return output;
}



