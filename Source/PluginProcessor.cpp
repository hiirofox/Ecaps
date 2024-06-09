/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "math.h"



//==============================================================================
EcapsAudioProcessor::EcapsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
	for (int j = 0; j < MaxNoteN; ++j)
	{
		Notes[j] = -1;
		NotesVelo[j] = 0;
		NotesFreq[j] = 0;
		NotesState[j] = 0;
	}

	for (int i = 0; i < 65536; ++i)//初始化正弦余弦表
	{
		cos_table[i] = cos((float)i * 2.0 * M_PI / 65536.0);
		sin_table[i] = sin((float)i * 2.0 * M_PI / 65536.0);
	}
	ad1l.SetSinTablePtr(sin_table, 65536);
	ad1r.SetSinTablePtr(sin_table, 65536);
	uni1l.SetCosTablePtr(cos_table, 65536);
	uni1r.SetCosTablePtr(cos_table, 65536);
	disp1l.SetCosTablePtr(cos_table, 65536);
	disp1r.SetCosTablePtr(cos_table, 65536);
}

juce::AudioProcessorValueTreeState::ParameterLayout EcapsAudioProcessor::createParameterLayout()
{
	juce::AudioProcessorValueTreeState::ParameterLayout layout;
	layout.add(std::make_unique<juce::AudioParameterFloat>("freq1", "FREQ1", 0.0, 1.0, 0.0));

	layout.add(std::make_unique<juce::AudioParameterFloat>("disp", "DISP", -1.0, 1.0, 0.0));

	layout.add(std::make_unique<juce::AudioParameterFloat>("upitch", "UPITCH", 0.0, 1.0, 0.0));

	layout.add(std::make_unique<juce::AudioParameterFloat>("sync", "SYNC", 0.0, 8.0, 1.0));

	layout.add(std::make_unique<juce::AudioParameterFloat>("octv", "OCTV", 0.0, 1.0, 0.0));
	layout.add(std::make_unique<juce::AudioParameterFloat>("harmv", "HARMV", 0.0, 1.0, 0.0));
	layout.add(std::make_unique<juce::AudioParameterFloat>("octdecay", "DECAY", 0.0, 1.0, 0.0));
	layout.add(std::make_unique<juce::AudioParameterFloat>("octmix", "MIX", 0.0, 1.0, 0.0));

	return layout;
}

EcapsAudioProcessor::~EcapsAudioProcessor()
{
	free(SynthData);
	SynthData = NULL;
}

//==============================================================================
const juce::String EcapsAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool EcapsAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool EcapsAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool EcapsAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double EcapsAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int EcapsAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int EcapsAudioProcessor::getCurrentProgram()
{
	return 0;
}

void EcapsAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String EcapsAudioProcessor::getProgramName(int index)
{
	return "Ecaps";
}

void EcapsAudioProcessor::changeProgramName(int index, const juce::String& newName)
{

}

//==============================================================================
void EcapsAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void EcapsAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EcapsAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
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

//Synth Data
typedef struct
{
	double ts[MaxNoteN];
}WvzoomData;

void EcapsAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::MidiMessage MidiMsg;//先处理midi事件
	int MidiTime;
	juce::MidiBuffer::Iterator MidiBuf(midiMessages);
	while (MidiBuf.getNextEvent(MidiMsg, MidiTime))
	{
		if (MidiMsg.isPitchWheel())
		{
			SyncPitch = (float)MidiMsg.getPitchWheelValue() / 8192.0 - 1.0;
			SyncPitch = pow(2.0, SyncPitch / 12.0);
		}
		if (MidiMsg.isNoteOn())
		{
			int note = MidiMsg.getNoteNumber();
		}
		if (MidiMsg.isNoteOff())
		{
			int note = MidiMsg.getNoteNumber();
		}
	}
	midiMessages.clear();


	WvzoomData* pData = (WvzoomData*)SynthData;//再处理合成器的数据
	if (SynthData == NULL)//init
	{
		SynthData = (void*)malloc(sizeof(WvzoomData));
		pData = (WvzoomData*)SynthData;
		memset(pData->ts, 0, sizeof(double) * MaxNoteN);
	}
	auto numSamples = buffer.getNumSamples();
	float* wavbufl = buffer.getWritePointer(0);
	float* wavbufr = buffer.getWritePointer(1);
	//const float* recbufl = buffer.getReadPointer(0);//因为是合成器所以不太需要输入
	//const float* recbufr = buffer.getReadPointer(1);

	float SampleRate = getSampleRate();
	float freq = *Params.getRawParameterValue("freq1");
	float disp = *Params.getRawParameterValue("disp");
	float unipitch = *Params.getRawParameterValue("upitch");
	float sync = *Params.getRawParameterValue("sync");

	float octv = *Params.getRawParameterValue("octv");
	float harmv = *Params.getRawParameterValue("harmv");
	float octdecay = *Params.getRawParameterValue("octdecay");
	float octmix = *Params.getRawParameterValue("octmix");

	freq = freq * freq * 5000;
	unipitch = unipitch * unipitch;
	ad1l.setFreq(freq);
	ad1r.setFreq(freq);
	uni1l.setUnisonNum(8);
	uni1r.setUnisonNum(8);
	uni1l.setPhase(0);
	uni1r.setPhase(0);
	uni1l.setSpeed(unipitch * 1000);
	uni1r.setSpeed(unipitch * 1100);

	disp1l.setPhase(0);
	disp1r.setPhase(0);
	disp1l.setSpeed(disp * 100000);
	disp1l.setSpeed(disp * 100000);

	sync1l.setSync(sync);
	sync1r.setSync(sync);

	octv = octv * octv;
	harmv = harmv * harmv;
	oct1l.setOctV(octv);
	oct1r.setOctV(octv);
	oct1l.setHarmV(harmv);
	oct1r.setHarmV(harmv);
	oct1l.setDecay(octdecay);
	oct1r.setDecay(octdecay);
	oct1l.setMix(octmix);
	oct1r.setMix(octmix);

	for (int i = 0; i < numSamples; ++i)
	{
		wt_counter++;
		if (wt_counter >= 80)//一会儿更新一次谐波
		{
			wt_counter = 0;

			ad1l.setAmplitude(0, (float)0.0);
			for (int j = 1; j < HarmonicNum; ++j)//初始化谐波(saw)
			{
				ad1l.setAmplitude(j, (float)1.0 / j);
				ad1r.setAmplitude(j, (float)1.0 / j);
				if (freq * j > 48000)//抗混叠
				{
					ad1l.setAmplitude(j, 0);
					ad1r.setAmplitude(j, 0);
				}
			}
			//应用谐波效果
			disp1l.apply(ad1l.getAmplitudePtr(), HarmonicNum);
			disp1l.apply(ad1r.getAmplitudePtr(), HarmonicNum);
			uni1l.apply(ad1l.getAmplitudePtr(), HarmonicNum);
			uni1r.apply(ad1r.getAmplitudePtr(), HarmonicNum);
			sync1l.apply(ad1l.getAmplitudePtr(), HarmonicNum);
			sync1r.apply(ad1r.getAmplitudePtr(), HarmonicNum);
			oct1l.apply(ad1l.getAmplitudePtr(), HarmonicNum);
			oct1r.apply(ad1r.getAmplitudePtr(), HarmonicNum);
		}

		float outl = ad1l.ProcWithFM(0, 0) * 0.1;
		float outr = ad1r.ProcWithFM(0, 0) * 0.1;
		wavbufl[i] = outl;
		wavbufr[i] = outr;
	}
}

//==============================================================================
bool EcapsAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EcapsAudioProcessor::createEditor()
{
	return new EcapsAudioProcessorEditor(*this);

	//return new juce::GenericAudioProcessorEditor(*this);//自动绘制(调试)
}

//==============================================================================

void EcapsAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
	auto state = Params.copyState();
	std::unique_ptr<juce::XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void EcapsAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
	{
		if (xmlState->hasTagName(Params.state.getType()))
		{
			Params.replaceState(juce::ValueTree::fromXml(*xmlState));
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new EcapsAudioProcessor();
}

//测试一下commit
