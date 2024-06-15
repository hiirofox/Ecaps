#include "FreqShifter.h"

HDSP::FreqShifter::FreqShifter()
{
}

HDSP::FreqShifter::~FreqShifter()
{
}

void HDSP::FreqShifter::setShift(float shift)
{
	x = shift;
}

void HDSP::FreqShifter::apply(float Amps[], int harmN)
{
	for (int i = 0; i < harmN; ++i)
	{
		tmp1[i] = 0;
	}
	for (int i = 0; i < harmN; ++i)
	{
		int pos = x + i;
		if (pos >= harmN - 1)break;
		else if (pos < 0)continue;
		float mix = x + i - pos;
		tmp1[pos] += Amps[i] * (1.0 - mix);
		tmp1[pos + 1] += Amps[i] * (mix);
	}
	for (int i = 1; i < harmN; ++i)//È¥µôÖ±Á÷£¡£¡
	{
		Amps[i] = tmp1[i];
	}
}
