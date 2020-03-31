#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyGeneratorComponent
	{
		BuoyancyGeneratorComponent(float _maxDepth = 10.0f, float _volume = 1.0f, float _liquidDensity = 1.0f,
			ECSEntity _liquid = ECSEntity(), Vector3 _centerOfBuoyancy = Vector3(0, 0, 0), ECSEntity _targetEntity = ECSEntity())
			: maxDepth(_maxDepth), volume(_volume), liquidDensity(_liquidDensity), liquid(_liquid), centerOfBuoyancy(_centerOfBuoyancy), targetEntity(_targetEntity)
		{

		}
		ECSEntity liquid;
		float maxDepth;
		float volume; // of object
		float liquidDensity;
		Vector3 centerOfBuoyancy;
		ECSEntity targetEntity;
	};
}
