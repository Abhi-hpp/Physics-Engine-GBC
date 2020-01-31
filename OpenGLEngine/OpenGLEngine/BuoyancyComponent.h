#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 0.0f, float _volume = 1.0f) : maxDepth(_maxDepth), volume(_volume)
		{

		}

		float maxDepth;
		float volume;
	};
}
