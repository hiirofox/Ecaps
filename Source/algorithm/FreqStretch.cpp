#include "FreqStretch.h"

HDSP::FreqStretch::FreqStretch()
{
}

HDSP::FreqStretch::~FreqStretch()
{
}

void HDSP::FreqStretch::setStretch(float stretch)
{
	x = stretch;
}

void HDSP::FreqStretch::apply(float Amps[], int harmN)
{
	for (int i = 0; i < harmN; ++i)
	{
		tmp1[i] = 0;
	}
	for (int i = 0; i < harmN; ++i)
	{
		int pos = x * i;
		if (pos >= harmN - 1)break;
		float mix = x * i - pos;
		tmp1[pos] += Amps[i] * (1.0 - mix);
		tmp1[pos + 1] += Amps[i] * (mix);
	}
	for (int i = 1; i < harmN; ++i)//去掉直流！！
	{
		Amps[i] = tmp1[i];
	}
}
