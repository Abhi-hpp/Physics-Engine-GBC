#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 10.0f, float _volume = 10.0f, float _waterHeight = 10.0f, float _liguidDensity = 1000.0f)
		{
			maxDepth = _maxDepth;
			volume = _volume;
			waterHeight = _waterHeight;
			liguidDensity = _liguidDensity;
		}

		float maxDepth;
		float volume;
		float waterHeight;
		float liguidDensity;
	};
}
