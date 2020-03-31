#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleSphereComponent
	{
		ParticleSphereComponent(float _radius = 1.0f)
			: radius(_radius)
		{

		}
		float radius;
	};
}
