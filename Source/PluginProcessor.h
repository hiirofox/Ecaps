/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "algorithm/alg.h"

static const int MaxNoteN = 32;//¸´ÒôÊý

//==============================================================================
/**
*/
class EcapsAudioProcessor : public juce::AudioProcessor
{
public:


	//==============================================================================
	EcapsAudioProcessor();
	~EcapsAudioProcessor() override;

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	//==============================================================================
	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String& newName) override;

	//==============================================================================
	void getStateInformation(juce::MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	//==============================================================================
	juce::AudioProcessorValueTreeState& GetParams()
	{
		return Params;
	}
private:
	//Synth Param
	static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
	juce::AudioProcessorValueTreeState Params{ *this, nullptr, "Parameters", createParameterLayout() };
	void* SynthData = NULL;

	float SyncPitch = 1.0;

	int Notes[MaxNoteN];//´æ¸öÐòºÅ
	float NotesFreq[MaxNoteN];//Òô·ûÆµÂÊ
	float NotesVelo[MaxNoteN];//Òô·ûÁ¦¶È
	float NotesState[MaxNoteN];//Òô·û×´Ì¬(note on/off)
	int NotePos = 0;
	//////////////////////////////////////////////////////////
	int wt_counter = 0;
	//////////////////////////////////////////////////////////
	float cos_table[65536];
	float sin_table[65536];
	HDSP::AdditiveCore ad1l;
	HDSP::AdditiveCore ad1r;

	HDSP::Unison uni1l;
	HDSP::Unison uni1r;

	HDSP::Disperse disp1l;
	HDSP::Disperse disp1r;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EcapsAudioProcessor)
};

