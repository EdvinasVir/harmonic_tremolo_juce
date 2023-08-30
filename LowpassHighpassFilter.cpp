/*
  ==============================================================================

    LowpassHighpassFilter.cpp
    Created: 26 Jul 2023 4:14:16pm
    Author:  37060

  ==============================================================================
*/

#include "LowpassHighpassFilter.h"

void LowpassHighpassFilter::setHighpass(bool highpass) {
	this->highpass = highpass;
}

void LowpassHighpassFilter::setCutoffFrequency(float cutoffFreq) {
	this->cutoffFreq = cutoffFreq;
}

void LowpassHighpassFilter::setSamplingRate(float samplingRate) {
	this->samplingRate = samplingRate;
}

void LowpassHighpassFilter::initialise(float samplingRate, bool highpass) {
	setSamplingRate(samplingRate);
	setHighpass(highpass);
}

void LowpassHighpassFilter::processBlock(juce::AudioBuffer<float>& buffer) {
	const float pi = 3.14159265358979323846;
	dnBuffer.resize(buffer.getNumChannels(), 0.0f);
	const float sign = highpass ? -1.0f : 1.0f;

	const float tan = std::tan(pi * cutoffFreq / samplingRate);
	const float a1 = (tan - 1.0f) / (tan + 1.0f);

	for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
		auto channelSamples = buffer.getWritePointer(channel);

		for (auto i = 0; i < buffer.getNumSamples(); ++i) {
			const auto inputSample = channelSamples[i];

			const auto allpassFilteredSample = a1 * inputSample + dnBuffer[channel];

			dnBuffer[channel] = inputSample - a1 * allpassFilteredSample;

			const auto filterOutput = 0.5f * (inputSample + sign * allpassFilteredSample);

			channelSamples[i] = filterOutput;
		}
	}
}
