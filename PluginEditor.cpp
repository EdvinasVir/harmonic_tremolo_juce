/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"

//==============================================================================
Harmonic_TremoloAudioProcessorEditor::Harmonic_TremoloAudioProcessorEditor(Harmonic_TremoloAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	addAndMakeVisible(cutoffFreqSlider);
	addAndMakeVisible(cutoffFreqLabel);

	addAndMakeVisible(lfoAmplitudeSlider);
	addAndMakeVisible(lfoAmplitudeLabel);

	addAndMakeVisible(lfoFreqSlider);
	addAndMakeVisible(lfoFreqLabel);

	addAndMakeVisible(wetSlider);
	addAndMakeVisible(wetLabel);

	cutoffFreqSlider.setTextValueSuffix("Hz");
	cutoffFreqLabel.setText("Cutoff Frequency", juce::dontSendNotification);
	cutoffFreqLabel.attachToComponent(&cutoffFreqSlider, false);

	lfoAmplitudeLabel.setText("LFO Amplitude", juce::dontSendNotification);
	lfoAmplitudeLabel.attachToComponent(&lfoAmplitudeSlider, false);

	lfoFreqSlider.setTextValueSuffix("Hz");
	lfoFreqLabel.setText("LFO Frequency", juce::dontSendNotification);
	lfoFreqLabel.attachToComponent(&lfoFreqSlider, false);

	wetLabel.setText("Wet", juce::dontSendNotification);
	wetLabel.attachToComponent(&wetSlider, false);

	cutoffFreqAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(
		vts, "cutoff_freq", cutoffFreqSlider));
	lfoAmplitudeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(
		vts, "lfo_amplitude", lfoAmplitudeSlider));
	lfoFreqAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(
		vts, "lfo_freq", lfoFreqSlider));
	wetAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(
		vts, "wet", wetSlider));

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 300);
}

Harmonic_TremoloAudioProcessorEditor::~Harmonic_TremoloAudioProcessorEditor()
{
}

//==============================================================================
void Harmonic_TremoloAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
}

void Harmonic_TremoloAudioProcessorEditor::resized()
{
	juce::Rectangle<int> bounds = getLocalBounds();

	juce::FlexBox flexboxRow1;
	flexboxRow1.flexDirection = juce::FlexBox::Direction::column;
	flexboxRow1.flexWrap = juce::FlexBox::Wrap::noWrap;
	flexboxRow1.alignContent = juce::FlexBox::AlignContent::spaceAround;

	juce::Array<juce::FlexItem> flexboxRow1Items;
	flexboxRow1Items.add(juce::FlexItem(bounds.getWidth() / 4.0, bounds.getHeight() / 8.0, cutoffFreqSlider));
	flexboxRow1Items.add(juce::FlexItem(100, bounds.getHeight() / 8.0, cutoffFreqLabel));

	flexboxRow1Items.add(juce::FlexItem(bounds.getWidth() / 4.0, bounds.getHeight() / 8.0, lfoAmplitudeSlider));
	flexboxRow1Items.add(juce::FlexItem(50, bounds.getHeight() / 8.0, lfoAmplitudeLabel));

	flexboxRow1Items.add(juce::FlexItem(bounds.getWidth() / 4.0, bounds.getHeight() / 8.0, lfoFreqSlider));
	flexboxRow1Items.add(juce::FlexItem(50, bounds.getHeight() / 8.0, lfoFreqLabel));

	flexboxRow1Items.add(juce::FlexItem(bounds.getWidth() / 4.0, bounds.getHeight() / 8.0, wetSlider));
	flexboxRow1Items.add(juce::FlexItem(50, bounds.getHeight() / 8.0, wetLabel));

	flexboxRow1.items = flexboxRow1Items;
	flexboxRow1.performLayout(bounds);
}
