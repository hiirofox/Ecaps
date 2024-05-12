#include "AdditiveCore.h"

#define M_PI 3.1415926535897932384626

HDSP::AdditiveCore::AdditiveCore()
{

	for (int i = 0; i < HarmonicNum; ++i)
	{
		hStates[i] = 0.0;
		hAmplitude[i] = 0.0;
		fOffset[i] = 0.0;
	}
}
HDSP::AdditiveCore::~AdditiveCore()
{
}
void HDSP::AdditiveCore::SetSinTablePtr(float sin_table[], int table_len)
{
	SinTable = sin_table;
	TableLen = table_len;
}
void HDSP::AdditiveCore::ResetPhase()
{
	for (int i = 0; i < HarmonicNum; ++i)
	{
		hStates[i] = 0.0;
	}
}
void HDSP::AdditiveCore::setFreq(float freq)
{
	_stride = (double)freq / SAMPLE_RATE * INT32_MAX;//对于波表来说,freq对应的步长
}
float* HDSP::AdditiveCore::getAmplitudePtr() { return hAmplitude; }
void HDSP::AdditiveCore::setAmplitude(int harmN, float value)
{
	hAmplitude[harmN] = value;
}

int32_t* HDSP::AdditiveCore::getFreqOffsetPtr() { return fOffset; }
void HDSP::AdditiveCore::setFreqOffset(int harmN, float offset)
{
	fOffset[harmN] = offset;
}

float HDSP::AdditiveCore::ProcWithFM(int32_t fm, int32_t fs)
{
	float val = 0;
	int32_t tmp1 = _stride + fm;
	int32_t tmp2 = 0;
	for (int i = 0; i < HarmonicNum; ++i)
	{
		hStates[i] += tmp2 + fOffset[i] + fs;
		tmp2 += tmp1;
		val += SinTable[(uint32_t)hStates[i] >> 16] * hAmplitude[i];
	}
	return val;
}
float HDSP::AdditiveCore::Proc()
{
	return ProcWithFM(0, 0);
}