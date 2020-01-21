#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleComponent
	{
		ParticleComponent(Vector3 _velocity = Vector3(0, 0, 0))
			:velocity(_velocity)
		{

		}
		Vector3 velocity;
	};
}
