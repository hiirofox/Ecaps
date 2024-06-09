#include "incfft.h"

HDSP::incfft::incfft()
{
}

HDSP::incfft::~incfft()
{
}



void HDSP::incfft::setLength(int length)
{
	len = length;
	pos = 0;
	dlyline.resize(len);
	ztable.resize(len);
	fq.resize(len);
	for (int i = 0; i < len; ++i)
	{
		ztable[i].re = cos(-2.0 * M_PI * i / len);
		ztable[i].im = sin(-2.0 * M_PI * i / len);
	}
}

void HDSP::incfft::push(complex_f32_t vin)
{
	complex_f32_t delta = csub(vin, dlyline[pos]);
	dlyline[pos] = vin;
	pos = (pos + 1) % len;
	for (int i = 0; i < len; ++i)//在时域的第一个元素进行加减等价于频域全局进行加减
	{//simd
		fq[i] = cadd(fq[i], delta);
	}
	for (int i = 0; i < len; ++i)//频域全局整个z^-1,相当于时域往后挪了，而且原本的最后一个变到第一个了。
	{//simd
		fq[i] = cmul(fq[i], ztable[i]);
	}
}


void HDSP::incfft::getFreqDomain(std::vector<complex_f32_t> obj)
{
	for (int i = 0; i < len; ++i)
	{
		obj[i] = fq[i];
	}
}
