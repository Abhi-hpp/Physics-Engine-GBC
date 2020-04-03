#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 2.0f,
			float _volume = 0.1f,
			float _waterHeight = 3.0f,
			float _liquidDensity = 1000.0f,
			ECSEntity _connectedEntityA = ECSEntity())
			: maxDepth(_maxDepth),
			volume(_volume),
			waterHeight(_waterHeight),
			liquidDensity(_liquidDensity),
			connectedEntityA(_connectedEntityA)
		{

		}
		float maxDepth;
		float volume;
		float waterHeight;
		float liquidDensity;
		ECSEntity connectedEntityA;
	};
}
