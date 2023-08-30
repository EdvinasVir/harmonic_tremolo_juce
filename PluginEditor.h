/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Harmonic_TremoloAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Harmonic_TremoloAudioProcessorEditor (Harmonic_TremoloAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~Harmonic_TremoloAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Harmonic_TremoloAudioProcessor& audioProcessor;
    juce::Slider cutoffFreqSlider;
    juce::Slider wetSlider;
    juce::Slider lfoAmplitudeSlider;
    juce::Slider lfoFreqSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoAmplitudeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFreqAttachment;

    juce::Label cutoffFreqLabel;
    juce::Label wetLabel;
    juce::Label lfoAmplitudeLabel;
    juce::Label lfoFreqLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Harmonic_TremoloAudioProcessorEditor)
};
