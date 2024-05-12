#include "Sync.h"

HDSP::Sync::Sync() { sync = 1; }
HDSP::Sync::~Sync() {}

void HDSP::Sync::setSync(float Sync) { sync = Sync; }

void HDSP::Sync::apply(float Amps[], int harmN)
{
	float tmp2[512];
	for (int i = 0; i < harmN; ++i)tmp2[i] = Amps[i];

	for (int partial_idx = 0; partial_idx < harmN; ++partial_idx) {
		float gain = 0.0f;

		for (int i = 1 - harmN; i < harmN; ++i) {
			auto idx = partial_idx + i;
			if (idx < 0 || idx >= harmN) {
				continue;
			}
			float sincv = Sinc_Func((partial_idx + 1) - (idx + 1) * sync);
			if (isnan(sincv) || sincv < -10 || sincv>10)sincv = 0.0;
			gain += tmp2[idx] * sincv;
		}
		Amps[partial_idx] = gain;
	}
}

float HDSP::Sinc_Func(float x)
{
	x *= 3.1415926535897932384626;
	if (fabs(x) < 0.001)return 1.0;
	return sin(x) / x;
}//
