#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleComponent
	{
		ParticleComponent(Vector3 _velocity = Vector3(0, 0, 0), float _radius = 1.0f, Color _color = Color::Green)
			: velocity(_velocity), radius(_radius), color(_color), acceleration(Vector3(0, 0, 0))
		{

		}
		Vector3 acceleration;
		Vector3 velocity;
		float radius;
		Color color;
	};
}
