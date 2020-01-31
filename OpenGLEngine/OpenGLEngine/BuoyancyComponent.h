#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 0.0f, float _volume = 0.0f)
			: volume(_volume), maxDepth(_maxDepth)
		{

		}
		float maxDepth;
		float volume;
	};
}
