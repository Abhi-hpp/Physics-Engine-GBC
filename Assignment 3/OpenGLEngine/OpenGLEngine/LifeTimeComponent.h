#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct LifeTimeComponent
	{
		LifeTimeComponent(float _maxTime = 10)
			:maxTime(_maxTime), timer(0), startSize(RANDOM_FLOAT(1.0f, 3.0f)), size(0)
		{

		}
		float maxTime;
		float timer;
		float startSize;
		float size;
	};
}
