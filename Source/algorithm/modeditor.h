#pragma once

#include "JuceHeader.h"

class modeditor :public juce::Component
{
public:
	virtual void setBounds(void setBounds(juce::Rectangle<int> newBounds));
	virtual void drawUI();
private:

};