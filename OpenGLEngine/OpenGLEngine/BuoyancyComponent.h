#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(ECSEntity _connectedEntity = ECSEntity(), float _liquidDensity = 1000.0f, float _radius = 5.0f, float _volume = 2.0f, float _maxDepth = 15.0f, float _waterHeight = 10.0f)
			: connectedEntity(_connectedEntity), liquidDensity(_liquidDensity), radius(_radius), volume(_volume), maxDepth(_maxDepth), waterHeight(_waterHeight)
		{

		}
		float radius;
		float volume;
		float maxDepth;
		float waterHeight;
		float liquidDensity;
		ECSEntity connectedEntity;
		Vector3 finalPos;
	};
}
