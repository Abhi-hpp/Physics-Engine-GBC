#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 5.f, float _volume = 10.f)
			:maxBuoyancyDepth(_maxDepth), buoyancyVolume(_volume)
		{

		}
		
		float maxBuoyancyDepth;
		float buoyancyVolume;
	};
}

