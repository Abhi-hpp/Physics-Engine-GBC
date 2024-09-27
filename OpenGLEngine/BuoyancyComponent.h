#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(ECSEntity _targetEntity = ECSEntity(), Vector3 _centerOfBuoyancy = Vector3(0, 0, 0),
			float _maxDepth = 1.0f, float _volume = 1.0f)
			: maxDepth(_maxDepth), volume(_volume),
			centerOfBuoyancy(_centerOfBuoyancy), targetEntity(_targetEntity)
		{

		}

		float maxDepth;
		float volume;
		Vector3 centerOfBuoyancy;
		ECSEntity targetEntity;
	};
}
