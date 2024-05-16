#pragma once

#include <math.h>
#include <string.h>

namespace HDSP
{
	class Octaver
	{
	private:
		float octv, harmv;
		//һ����ֻ����8�ȣ���һ���ǵ���ÿ��г��
		float decay, mix;
		//���ӵ�˥���ȣ�֮���

	public:
		Octaver();
		~Octaver();

		void setOctV(float Octave);
		void setHarmV(float Harmonic);
		void setDecay(float Decay);
		void setMix(float Mix);

		void apply(float Amps[], int harmN);
	};
}