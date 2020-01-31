#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct DragForceComponent
	{
		DragForceComponent(float _k1 = 0.0f, float _k2 = 0.0f) : k1(_k1), k2(_k2)
		{

		}
		float k1;
		float k2;
	};
}
