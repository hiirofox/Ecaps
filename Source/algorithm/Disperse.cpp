#include "Disperse.h"

#define M_PI 3.1415926535897932384626

HDSP::Disperse::Disperse() { t = 0; }
HDSP::Disperse::~Disperse() {}
void HDSP::Disperse::reset() { t = phase; }

void HDSP::Disperse::SetCosTablePtr(float* tablePtr, int tableLen) { cos_table = tablePtr; table_len = tableLen; }
void HDSP::Disperse::setPhase(float Phase) { phase = Phase; }
void HDSP::Disperse::setSpeed(int32_t Speed) { speed = Speed; }
void HDSP::Disperse::setPan(float Pan) { pan = Pan; }

void HDSP::Disperse::apply(float* Amps, int harmN)
{
	t += speed;
	for (int i = 0; i < harmN; ++i)
	{
		Amps[i] *= cos_table[(uint32_t)(i * i * t) >> 16];
	}
}