#pragma once

#include <math.h>
#include "complex.h"

namespace HDSP {
	void fft_f32(complex_f32_t* a, int n, int inv);
}