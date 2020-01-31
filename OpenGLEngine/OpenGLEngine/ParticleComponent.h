#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleComponent
	{
		ParticleComponent(Vector3 _velocity = Vector3(0, 0, 0), Color _colour = Color::Magenta)
			:velocity(_velocity), acceleration(Vector3(0, 0, 0)), colour(_colour)
		{

		}
		Vector3 acceleration;
		Vector3 velocity;
		Color colour;
	};
}
