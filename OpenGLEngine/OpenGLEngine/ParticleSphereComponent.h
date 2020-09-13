#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleSphereComponent
	{
		ParticleSphereComponent(float _radius = 1.f, float _mass = 1.0f)
			: radius(_radius),
			mass(_radius)
		{
		}
		float radius;
		float mass;
	};
}
