/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EcapsAudioProcessorEditor::EcapsAudioProcessorEditor(EcapsAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(640, 480);

	S_FREQ1.setText("FREQ1");//唅聽場宎趙
	S_FREQ1.ParamLink(audioProcessor.GetParams(), "freq1");
	S_DISP1.setText("disp");//唅聽場宎趙
	S_DISP1.ParamLink(audioProcessor.GetParams(), "disp");
	S_UPITCH.setText("UPitch");
	S_UPITCH.ParamLink(audioProcessor.GetParams(), "upitch");
	S_SYNC.setText("SYNC");
	S_SYNC.ParamLink(audioProcessor.GetParams(), "sync");
	addAndMakeVisible(S_FREQ1);
	addAndMakeVisible(S_DISP1);
	addAndMakeVisible(S_UPITCH);
	addAndMakeVisible(S_SYNC);
}

EcapsAudioProcessorEditor::~EcapsAudioProcessorEditor()
{
}

//==============================================================================
void EcapsAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(juce::Colour(0x00, 0x00, 0x00));

	//g.setColour (juce::Colours::white);
	//g.setFont (15.0f);
	//g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EcapsAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	S_FREQ1.setPos(32 + 64 * 0, 32);
	S_DISP1.setPos(32 + 64 * 1, 32);
	S_UPITCH.setPos(32 + 64 * 2, 32);
	S_SYNC.setPos(32 + 64 * 3, 32);
}
