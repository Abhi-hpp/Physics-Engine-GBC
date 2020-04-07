#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct LifeTimeComponent
	{
<<<<<<< Updated upstream
		LifeTimeComponent(float _maxTime = 10)
			:maxTime(_maxTime), timer(0), startSize(RANDOM_FLOAT(1.0f, 3.0f)), size(0)
=======
		LifeTimeComponent(float _maxTime = 5, Color _color = Color::Green)
			:maxTime(_maxTime), timer(0), color(_color)
>>>>>>> Stashed changes
		{

		}
		float maxTime;
		float timer;
<<<<<<< Updated upstream
		float startSize;
		float size;
=======
		Color color;
>>>>>>> Stashed changes
	};
}
