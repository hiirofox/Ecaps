#pragma once

#include "modplug.h"
#include "modeditor.h"

namespace HDSP
{
	class FreqStretch :public modpulg, modeditor
	{
	private:
		float x;
		float tmp1[512];
	public:
		FreqStretch();
		~FreqStretch();
		void setStretch(float stretch);
		void apply(float Amps[], int harmN);
	};
}