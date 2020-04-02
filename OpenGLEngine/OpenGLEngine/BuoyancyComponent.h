#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(ECSEntity _targetEntity = ECSEntity(), Vector3 _centerOfBuoyancy = Vector3(0, 0, 0), float _maxDepth = 0, float _volume = 0) :
			targetEntity(_targetEntity), centerOfBuoyancy(_centerOfBuoyancy), maxDepth(_maxDepth), volume(_volume)
		{

		}

		ECSEntity targetEntity;
		Vector3 centerOfBuoyancy;
		float maxDepth;
		float volume;
	};
}
