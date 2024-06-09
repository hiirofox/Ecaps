#include "Octaver.h"

HDSP::Octaver::Octaver() {}
HDSP::Octaver::~Octaver() {}

void HDSP::Octaver::setOctV(float Octave) { octv = Octave; }
void HDSP::Octaver::setHarmV(float Harmonic) { harmv = Harmonic; }
void HDSP::Octaver::setDecay(float Decay) { decay = Decay; }
void HDSP::Octaver::setMix(float Mix) { mix = Mix; }

void HDSP::Octaver::apply(float Amps[], int harmN)
{
	memset(tmp1, 0, sizeof(tmp1));
	for (int i = 1; i < harmv * harmN; ++i)//harm
	{
		for (int j = i, k = 1; j < harmN; j += i, k++)
		{
			float v = Amps[k];
			v = decay * (v / i) + (1.0 - decay) * v;
			tmp1[j] += v;
		}
	}

	for (int i = 1; i < octv * harmN; i += i)//octave
	{
		for (int j = i, k = 1; j < harmN; j += i, k++)
		{
			float v = Amps[k];
			v = decay * (v / i) + (1.0 - decay) * v;
			tmp1[j] += v;
		}
	}

	for (int i = 0; i < harmN; ++i)
	{
		Amps[i] = tmp1[i] * mix + Amps[i] * (1.0 - mix);
	}
}