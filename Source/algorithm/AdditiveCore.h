#pragma once

#include <math.h>
#include <stdint.h>

#define HarmonicNum 512
#define SAMPLE_RATE 48000//采样率,先固定了

namespace HDSP
{
	class AdditiveCore//加法合成器的核心(当一个振荡器用)
	{
	private:
		int32_t hStates[HarmonicNum];//计数器
		int32_t fOffset[HarmonicNum];//频率偏移(线性),按谐波分
		float hAmplitude[HarmonicNum];//谐波振幅
		float* SinTable;//cos的表
		int TableLen = 65536;//cos表的长度
		int32_t _stride;//内部单位 一个单位的步长
	public:
		AdditiveCore();
		~AdditiveCore();
		void SetSinTablePtr(float cos_table[], int table_len);
		void ResetPhase();//重置相位
		void setFreq(float freq);//设置频率,单位hz
		void setAmplitude(int harmN, float value);//(针对每个谐波)改变振幅
		float* getAmplitudePtr();
		void setFreqOffset(int harmN, float offset);
		int32_t* getFreqOffsetPtr();
		float ProcWithFM(int32_t fm, int32_t fs);//获取一个采样(fm)
		float Proc();
	};
	//好了，你现在已经有了一个完整的加法核心了，开始制造加法合成器吧
}