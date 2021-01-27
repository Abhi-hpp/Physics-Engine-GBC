#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct LifeTimeComponent
	{
		LifeTimeComponent(float _maxTime = 5, Color _color = Color::Green)
			:maxTime(_maxTime), timer(0), color(_color)
		{

		}
		float maxTime;
		float timer;
		Color color;
	};
}
