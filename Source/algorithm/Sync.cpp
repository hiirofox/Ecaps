#include "Sync.h"
#include <cassert>

HDSP::Sync::Sync() { sync = 1; }
HDSP::Sync::~Sync() {}

void HDSP::Sync::setSync(float Sync) { sync = Sync; }
/*
void HDSP::Sync::apply(float Amps[], int harmN)//sinc卷积
{
	float tmp2[512];
	for (int i = 0; i < harmN; ++i)tmp2[i] = Amps[i];

	for (int partial_idx = 1; partial_idx < harmN; ++partial_idx) {
		float gain = 0.0f;

		for (int i = 1 - harmN; i < harmN; ++i) {
			int idx = partial_idx + i;
			if (idx <= 0 || idx >= harmN) {
				continue;
			}
			gain += tmp2[idx] * Sinc_Func((float)partial_idx - sync * idx);
		}
		Amps[partial_idx] = gain;
	}
}*/

/*
void HDSP::Sync::apply(float Amps[], int harmN)//fft
{
	HDSP::complex_f32_t tmp1[512];
	memset(tmp1, 0, sizeof(tmp1));
	for (int i = 1; i < harmN; ++i)
	{
		tmp1[i].re = Amps[i];
		tmp1[i].im = 0;
	}
	HDSP::fft_f32(tmp1, harmN, -1);//ifft

	HDSP::complex_f32_t tmp2[1024];
	memset(tmp2, 0, sizeof(tmp2));
	for (int i = 0; i < 1024; ++i)
	{
		float v = sync * i / 1024.0;
		int j = (v - (int)v) * harmN;
		tmp2[i].re = tmp1[j].re / 1024.0;
		tmp2[i].im = 0;
	}

	HDSP::fft_f32(tmp2, 1024, 1);//fft
	for (int i = 1; i < harmN; ++i)
	{
		Amps[i] = tmp2[i].re;
	}
}*/

void HDSP::Sync::apply(float Amps[], int harmN)//假的sync,听起来挺像,而且快
{
	float tmp1[512];
	memset(tmp1, 0, sizeof(tmp1));
	for (int i = 1; i < 512; ++i)
	{
		int j = sync * i;
		if (j >= harmN - 1)break;
		float mix = sync * i;
		mix = mix - (int)mix;
		tmp1[j] += Amps[i] * (1.0 - mix);
		tmp1[j + 1] += Amps[i] * mix;
	}
	for (int i = 1; i < 512; ++i)
		Amps[i] = tmp1[i];
}

float HDSP::Sinc_Func(float x)
{
	x *= 3.1415926535897932384626;
	if (fabs(x) < 0.01)return 1.0;
	return sin(x) / x;
}
