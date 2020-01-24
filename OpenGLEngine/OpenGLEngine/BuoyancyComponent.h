#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 5.f, float _volume = 10.f)
			:maxDepth(_maxDepth), volume(_volume)
		{

		}
		
		float maxDepth;
		float volume;
	};
}

