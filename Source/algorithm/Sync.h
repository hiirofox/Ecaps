#pragma once

#define _USE_MATH_DEFINES
#include <string.h>
#include <math.h>
#include "math/fft.h"

namespace HDSP
{
	class Sync
	{
	private:
		float sync;

		HDSP::complex_f32_t tmp1[512];
		HDSP::complex_f32_t tmp2[1024];
	public:
		Sync();
		~Sync();
		void setSync(float Sync);
		void apply(float Amps[], int harmN);
	};
	float Sinc_Func(float x);
}