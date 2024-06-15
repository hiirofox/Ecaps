#pragma once

#include <math.h>
#include "modplug.h"
#include "modeditor.h"

namespace HDSP
{
	class FreqShifter :public modpulg, modeditor
	{
	private:
		float x;
		float tmp1[512];
	public:
		FreqShifter();
		~FreqShifter();
		void setShift(float shift);
		void apply(float Amps[], int harmN);
	};
}