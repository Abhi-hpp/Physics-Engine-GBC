#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyCenterComponent
	{
		BuoyancyCenterComponent(Vector3 _positionOffset = Vector3(0, 0, 0), float _maxDepth = 1.0f, float _volume = 1.0f)
			: positionOffset(_positionOffset), maxDepth(_maxDepth), volume(_volume)
		{

		}

		Vector3 positionOffset;
		float maxDepth;
		float volume;
	};
}
