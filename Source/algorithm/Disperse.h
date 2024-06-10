#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "modplug.h"
#include "modeditor.h"

namespace HDSP
{
	class Disperse :public modpulg, public modeditor
	{
	private:
		int32_t t;
		float phase, speed, pan;
		float* cos_table;
		int table_len = 65536;
	public:
		Disperse();
		~Disperse();
		void reset();
		void SetCosTablePtr(float* tablePtr, int table_len);
		void setPhase(float Phase);
		void setSpeed(int32_t Speed);
		void setPan(float Pan);
		void apply(float* Amps, int harmN);
	};
}