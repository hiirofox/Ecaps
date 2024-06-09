#pragma	once

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <vector>
#include "complex.h"

namespace HDSP {
	class incfft
	{
	private:
		int len, pos;
		std::vector<complex_f32_t> dlyline;
		std::vector<complex_f32_t> ztable;//��z^-1�ı�
		std::vector<complex_f32_t> fq;//Ƶ�������
	public:
		incfft();
		~incfft();
		void setLength(int length);
		void push(complex_f32_t vin);
		void getFreqDomain(std::vector <complex_f32_t> obj);
	};
}