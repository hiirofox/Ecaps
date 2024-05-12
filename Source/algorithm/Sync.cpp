#include "Sync.h"
#include <cassert>

HDSP::Sync::Sync() { sync = 1; }
HDSP::Sync::~Sync() {}

void HDSP::Sync::setSync(float Sync) { sync = Sync; }

void HDSP::Sync::apply(float Amps[], int harmN)
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
}

float HDSP::Sinc_Func(float x)
{
	x *= 3.1415926535897932384626;
	if (fabs(x) < 0.01)return 1.0;
	return sin(x) / x;
}
