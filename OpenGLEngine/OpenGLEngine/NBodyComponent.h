#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _mass = 50.0f, float _g = 1.0f, float _maxSpeed = 5.0f)
			: mass(_mass), g(_g), maxSpeed(_maxSpeed)
		{

		}
		float mass;
		float g = 1.0f; // Gravitational Constant
		float maxSpeed = 5.0f; // Clamped Speed
	};
}