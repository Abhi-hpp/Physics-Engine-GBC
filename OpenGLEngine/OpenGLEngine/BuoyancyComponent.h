#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 10.0f, float _volume = 1.0f, float _liquidDensity = 1.0f, ECSEntity _liquid = ECSEntity())
			:  maxDepth(_maxDepth), volume(_volume), liquidDensity(_liquidDensity), liquid(_liquid)
		{

		}
		ECSEntity liquid;
		float maxDepth;
		float volume; // of object
		float liquidDensity;
	};
}
