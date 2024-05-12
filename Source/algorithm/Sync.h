#pragma once

#include <math.h>
#include <string.h>
#include <math.h>
#include "math/fft.h"

namespace HDSP
{
	class Sync
	{
	private:
		float sync;
	public:
		Sync();
		~Sync();
		void setSync(float Sync);
		void apply(float Amps[], int harmN);
	};
	float Sinc_Func(float x);
}