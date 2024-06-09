#include "Unison.h"

#define M_PI 3.1415926535897932384626

HDSP::Unison::Unison()
{
	t = 0;
	for (int i = 0; i < 512; ++i)
	{
		rnd[i] = rand() % 50000;
	}
}

HDSP::Unison::~Unison() {}
void HDSP::Unison::reset() { t = phase; }
void HDSP::Unison::SetCosTablePtr(float* tablePtr, int tableLen) { cos_table = tablePtr; table_len = tableLen; }
void HDSP::Unison::setPhase(float Phase) { phase = Phase; }
void HDSP::Unison::setSpeed(int32_t Speed) { speed = Speed; }
void HDSP::Unison::setPan(float Pan) { pan = Pan; }
void HDSP::Unison::setUnisonNum(int Num) { num = Num; }

void HDSP::Unison::apply(float* Amps, int harmN)
{
	t += speed;
	float tmp = 0;
	float balance = pow(sqrt(2), num);
	for (int i = 0; i < harmN; ++i)
	{
		tmp = 0;
		for (int j = 0; j < num; ++j)
		{
			tmp += cos_table[(uint32_t)(i * t * rnd[j]) >> 16];
		}
		//Amps[i] *= tmp * balance;//这个是相当于叠加每个振荡器
		Amps[i] *= tmp;//这个就能量平均了
	}
}