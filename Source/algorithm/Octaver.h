#pragma once

#include <math.h>
#include <string.h>

namespace HDSP
{
	class Octaver
	{
	private:
		float octv, harmv;
		//一种是只叠加8度，另一种是叠加每个谐波
		float decay, mix;
		//叠加的衰减度，之类的

		float tmp1[512];
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