#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(Vector3 _cubeScale = Vector3(0, 0, 0), float _maxDepth = 0, float _volume = 0) :
			cubeScale(_cubeScale), maxDepth(_maxDepth), volume(_volume)
		{

		}

		Vector3 cubeScale;

		float maxDepth;
		float volume;
	};
}
