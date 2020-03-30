#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(ECSEntity _targetEntity = ECSEntity(), float _maxDepth = 5.f, float _volume = 10.f, Vector3 _localOffset = Vector3(0, 0, 0))
			:targetEntity(_targetEntity), maxDepth(_maxDepth), volume(_volume), localOffset(_localOffset)
		{

		}
		
		ECSEntity targetEntity;
		float maxDepth;
		float volume;
		Vector3 localOffset;
	};
}

