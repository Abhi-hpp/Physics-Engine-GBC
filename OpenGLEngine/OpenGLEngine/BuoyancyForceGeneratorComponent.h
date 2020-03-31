#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyForceGeneratorComponent
	{
		BuoyancyForceGeneratorComponent(float _maxDepth = 10.0f, float _volume = 1.0f, float _liquidDensity = 1.0f,
			ECSEntity _liquid = ECSEntity(), Vector3 _centerOfBuoyancy = Vector3(0, 0, 0), ECSEntity _attachedEntity = ECSEntity())
			: maxDepth(_maxDepth), volume(_volume), liquidDensity(_liquidDensity), liquid(_liquid), centerOfBuoyancy(_centerOfBuoyancy), attachedEntity(_attachedEntity)
		{

		}

	public:
		ECSEntity liquid;
		Vector3 centerOfBuoyancy;
		ECSEntity attachedEntity;
		float maxDepth;
		float volume;
		float liquidDensity;

	};
}
