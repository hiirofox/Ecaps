/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ui\LM_slider.h"

//==============================================================================
/**
*/
class EcapsAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	EcapsAudioProcessorEditor(EcapsAudioProcessor&);
	~EcapsAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	EcapsAudioProcessor& audioProcessor;

	LMKnob S_FREQ1;
	LMKnob S_DISP1;
	LMKnob S_UPITCH;
	LMKnob S_SYNC;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EcapsAudioProcessorEditor)
};
