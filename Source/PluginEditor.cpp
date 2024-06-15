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
	S_DISP1.setText("disp");//唅聽場宎趙
	S_UPITCH.setText("UPitch");
	S_SYNC.setText("SYNC");

	S_OCTV.setText("OCTV");
	S_HARMV.setText("HARMV");
	S_OCTDECAY.setText("DECAY");
	S_OCTMIX.setText("MIX");
	S_FSTC.setText("FStretch");
	S_FSHIFT.setText("FShift");

	S_FREQ1.ParamLink(audioProcessor.GetParams(), "freq1");
	S_DISP1.ParamLink(audioProcessor.GetParams(), "disp");
	S_UPITCH.ParamLink(audioProcessor.GetParams(), "upitch");
	S_SYNC.ParamLink(audioProcessor.GetParams(), "sync");
	S_OCTV.ParamLink(audioProcessor.GetParams(), "octv");
	S_HARMV.ParamLink(audioProcessor.GetParams(), "harmv");
	S_OCTDECAY.ParamLink(audioProcessor.GetParams(), "octdecay");
	S_OCTMIX.ParamLink(audioProcessor.GetParams(), "octmix");
	S_FSTC.ParamLink(audioProcessor.GetParams(), "stretch");
	S_FSHIFT.ParamLink(audioProcessor.GetParams(), "fshift");

	addAndMakeVisible(S_FREQ1);
	addAndMakeVisible(S_DISP1);
	addAndMakeVisible(S_UPITCH);
	addAndMakeVisible(S_SYNC);

	addAndMakeVisible(S_OCTV);
	addAndMakeVisible(S_HARMV);
	addAndMakeVisible(S_OCTDECAY);
	addAndMakeVisible(S_OCTMIX);

	addAndMakeVisible(S_FSTC);
	addAndMakeVisible(S_FSHIFT);
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


	S_OCTV.setPos(32 + 64 * 4, 32 + 64 * 0);
	S_HARMV.setPos(32 + 64 * 4, 32 + 64 * 1);
	S_OCTDECAY.setPos(32 + 64 * 4, 32 + 64 * 2);
	S_OCTMIX.setPos(32 + 64 * 4, 32 + 64 * 3);
	
	S_FSTC.setPos(32 + 64 * 5, 32 + 64 * 0);
	S_FSHIFT.setPos(32 + 64 * 6, 32 + 64 * 0);
}
