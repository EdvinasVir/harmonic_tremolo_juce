/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Harmonic_TremoloAudioProcessor::Harmonic_TremoloAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	),
#else 
	:
#endif
parameters(*this, nullptr, juce::Identifier("HarmonicTremoloPlugin"),
	{ std::make_unique<juce::AudioParameterFloat>("cutoff_freq",
	"Cutoff Frequency",
	juce::NormalisableRange{500.0f, 5000.0f, 0.1f, 0.2f, false}, 2250.0f),
std::make_unique<juce::AudioParameterFloat>("wet",
	"Wet",
	juce::NormalisableRange{0.0f, 1.0f, 0.01f, 1.0f, false}, 0.5f),
std::make_unique<juce::AudioParameterFloat>("lfo_freq",
	"LFO Frequency",
	juce::NormalisableRange{0.1f, 5.0f, 0.1f, 1.0f, false}, 1.0f),
std::make_unique<juce::AudioParameterFloat>("lfo_amplitude",
	"LFO Amplitude",
	juce::NormalisableRange{0.0f, 1.0f, 0.01f, 1.0f, false}, 1.0f) }
)
{
	cutoffFrequencyParameter = parameters.getRawParameterValue("cutoff_freq");
	wetParameter = parameters.getRawParameterValue("wet");
	lfoFreqParameter = parameters.getRawParameterValue("lfo_freq");
	lfoAmplitudeParameter = parameters.getRawParameterValue("lfo_amplitude");
}

Harmonic_TremoloAudioProcessor::~Harmonic_TremoloAudioProcessor()
{
}

//==============================================================================
const juce::String Harmonic_TremoloAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool Harmonic_TremoloAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool Harmonic_TremoloAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool Harmonic_TremoloAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double Harmonic_TremoloAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int Harmonic_TremoloAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int Harmonic_TremoloAudioProcessor::getCurrentProgram()
{
	return 0;
}

void Harmonic_TremoloAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String Harmonic_TremoloAudioProcessor::getProgramName(int index)
{
	return {};
}

void Harmonic_TremoloAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void Harmonic_TremoloAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	harmonicTremolo.initialise(sampleRate, getTotalNumInputChannels(), samplesPerBlock);
}

void Harmonic_TremoloAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Harmonic_TremoloAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void Harmonic_TremoloAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	
	const auto cutoffFrequency = cutoffFrequencyParameter->load();
	const auto lfoAmplitude = lfoAmplitudeParameter->load();
	const auto lfoFrequency = lfoFreqParameter->load();
	const auto wet = wetParameter->load();

	harmonicTremolo.setfilterCutoff(cutoffFrequency);
	harmonicTremolo.setLfoAmplitude(lfoAmplitude);
	harmonicTremolo.setLfoFrequency(lfoFrequency);
	harmonicTremolo.setWet(wet);

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	harmonicTremolo.processBlock(buffer);
}

//==============================================================================
bool Harmonic_TremoloAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Harmonic_TremoloAudioProcessor::createEditor()
{
	return new Harmonic_TremoloAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void Harmonic_TremoloAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void Harmonic_TremoloAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new Harmonic_TremoloAudioProcessor();
}
