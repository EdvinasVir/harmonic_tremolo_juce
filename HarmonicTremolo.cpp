/*
  ==============================================================================

	HarmonicTremolo.cpp
	Created: 26 Jul 2023 4:13:40pm
	Author:  37060

  ==============================================================================
*/

#include "HarmonicTremolo.h"

void HarmonicTremolo::setfilterCutoff(float cutoffFrequency) {
	lowpass.setCutoffFrequency(cutoffFrequency);
	highpass.setCutoffFrequency(cutoffFrequency);
}

void HarmonicTremolo::setSamplingRate(float samplingRate) {
	this->samplingRate = samplingRate;
}

void HarmonicTremolo::setLfoAmplitude(float amplitude) {
	lfo.setAmplitude(amplitude);
}

void HarmonicTremolo::setLfoFrequency(float freq) {
	lfo.setFrequency(freq);
}

void HarmonicTremolo::setWet(float wet) {
	this->wet = wet;
}

void HarmonicTremolo::initialise(float samplingRate, int numChannels, int buffSize) {
	setSamplingRate(samplingRate);
	lowpass.initialise(samplingRate, false);
	highpass.initialise(samplingRate, true);
	lfo.initialise(samplingRate);
}

void HarmonicTremolo::processBlock(juce::AudioBuffer<float>& buffer) {
	lowpassBuff.makeCopyOf(buffer);
	highpassBuff.makeCopyOf(buffer);

	lowpass.processBlock(lowpassBuff);
	highpass.processBlock(highpassBuff);
	
	for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
		auto channelSamples = buffer.getWritePointer(channel);
		auto lowpassChannelSamples = lowpassBuff.getWritePointer(channel);
		auto highpassChannelSamples = highpassBuff.getWritePointer(channel);

		for (auto i = 0; i < buffer.getNumSamples(); ++i) {
			lowpassChannelSamples[i] = lowpassChannelSamples[i] * lfo.renderSample();
			highpassChannelSamples[i] = highpassChannelSamples[i] * (1 - lfo.renderSample());
			channelSamples[i] = ((lowpassChannelSamples[i] + highpassChannelSamples[i]) * 0.5f);
		}
	}
}