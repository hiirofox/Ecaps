#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdint.h>

namespace HDSP
{
	class Unison
	{
	private:
		int32_t t;
		float phase, speed, pan;
		int num;
		int32_t rnd[512];
		float* cos_table;
		int table_len = 65536;
	public:
		Unison();
		~Unison();
		void reset();
		void SetCosTablePtr(float* tablePtr, int table_len);
		void setPhase(float Phase);
		void setSpeed(int32_t Speed);
		void setPan(float Pan);
		void setUnisonNum(int Num);
		void apply(float* Amps, int harmN);
	};
}