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
	for (int i = 0; i < len; ++i)//��ʱ��ĵ�һ��Ԫ�ؽ��мӼ��ȼ���Ƶ��ȫ�ֽ��мӼ�
	{//simd
		fq[i] = cadd(fq[i], delta);
	}
	for (int i = 0; i < len; ++i)//Ƶ��ȫ������z^-1,�൱��ʱ������Ų�ˣ�����ԭ�������һ���䵽��һ���ˡ�
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
