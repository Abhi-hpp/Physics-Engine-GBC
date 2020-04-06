#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 10.0f, float _volume = 10.0f, float _waterHeight = 10.0f, float _liquidDensity = 10.0f)
			:maxDepth(_maxDepth), volume(_volume), waterHeight(_waterHeight), liquidDensity(_liquidDensity)
		{
		}

		float maxDepth;
		float volume;
		float waterHeight;
		float liquidDensity;
	};
}
