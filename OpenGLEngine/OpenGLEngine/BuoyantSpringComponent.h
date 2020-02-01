#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyantSpringComponent
	{
		BuoyantSpringComponent(float _maxDepth = 5.0f, float _volume = 10.0f)
			:maxDepth(_maxDepth), volume(_volume)
		{

		}
		float maxDepth;
		float volume;
	};
}
