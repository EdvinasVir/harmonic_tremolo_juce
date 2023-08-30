/*
  ==============================================================================

    HarmonicTremolo.h
    Created: 26 Jul 2023 4:13:40pm
    Author:  37060

  ==============================================================================
*/

#pragma once

#include "LowpassHighpassFilter.h"
#include "Lfo.h"

class HarmonicTremolo
{
public: 
	void setfilterCutoff(float cutoffFreq);
	void setLfoAmplitude(float amplitude);
	void setLfoFrequency(float lfoFreq);
	void setWet(float wet);
	void initialise(float samplingRate, int numChannels, int buffSize);
	void processBlock(juce::AudioBuffer<float>& buffer);

private:
	void setSamplingRate(float samplingRate);

	juce::AudioBuffer<float> lowpassBuff;
	juce::AudioBuffer<float> highpassBuff;

	float samplingRate;
	int cutoffFrequency;
	int wet;

	LowpassHighpassFilter lowpass;
	LowpassHighpassFilter highpass;
	Lfo lfo;
};

