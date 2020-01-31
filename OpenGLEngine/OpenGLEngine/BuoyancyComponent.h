#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 10.0f, float _volume = 100.0f, float _waterHeight = 10.0f, ECSEntity _buoy = ECSEntity(), float _density = 1000.0f)
			: maxDepth(_maxDepth),
			volume(_volume),
			waterHeight(_waterHeight),
			buoyEntity(_buoy),
			density(_density)
		{

		}
		float maxDepth,
			volume,
			waterHeight,
			density,
			waterXWidth,
			waterZWidth;
		ECSEntity buoyEntity;
	};
}