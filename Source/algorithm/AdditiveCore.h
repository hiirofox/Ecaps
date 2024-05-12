#pragma once

#include <math.h>
#include <stdint.h>

#define HarmonicNum 512
#define SAMPLE_RATE 48000//������,�ȹ̶���

namespace HDSP
{
	class AdditiveCore//�ӷ��ϳ����ĺ���(��һ��������)
	{
	private:
		int32_t hStates[HarmonicNum];//������
		int32_t fOffset[HarmonicNum];//Ƶ��ƫ��(����),��г����
		float hAmplitude[HarmonicNum];//г�����
		float* SinTable;//cos�ı�
		int TableLen = 65536;//cos��ĳ���
		int32_t _stride;//�ڲ���λ һ����λ�Ĳ���
	public:
		AdditiveCore();
		~AdditiveCore();
		void SetSinTablePtr(float cos_table[], int table_len);
		void ResetPhase();//������λ
		void setFreq(float freq);//����Ƶ��,��λhz
		void setAmplitude(int harmN, float value);//(���ÿ��г��)�ı����
		float* getAmplitudePtr();
		void setFreqOffset(int harmN, float offset);
		int32_t* getFreqOffsetPtr();
		float ProcWithFM(int32_t fm, int32_t fs);//��ȡһ������(fm)
		float Proc();
	};
	//���ˣ��������Ѿ�����һ�������ļӷ������ˣ���ʼ����ӷ��ϳ�����
}