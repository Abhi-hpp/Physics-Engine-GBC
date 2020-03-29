#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyantSpringComponent
	{
		BuoyantSpringComponent(ECSEntity _targetEntity = ECSEntity(),float _maxDepth = 5.0f, float _volume = 10.0f, Vector3 _offset = Vector3(0, 0, 0))
			:targetEntity(_targetEntity), maxDepth(_maxDepth), volume(_volume), offset(_offset)
		{

		}

		ECSEntity targetEntity;
		float maxDepth;
		float volume;
		Vector3 offset;
	};
}
