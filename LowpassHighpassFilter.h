/*
  ==============================================================================

    LowpassHighpassFilter.h
    Created: 26 Jul 2023 4:14:16pm
    Author:  37060

  ==============================================================================
*/

#pragma once

#include <vector>
#include "JuceHeader.h"

class LowpassHighpassFilter
{
public:
	void setHighpass(bool highpass);
	void setCutoffFrequency(float cutoffFreq);
	void setSamplingRate(float samplingRate);
	void processBlock(juce::AudioBuffer<float>& buffer);
	void initialise(float samplingRate, bool highpass);

private:
	bool highpass;
	float cutoffFreq;
	float samplingRate;
	std::vector<float> dnBuffer;
};
