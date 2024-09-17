#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _mass = 10.0f, Color _color = Color::Green)
			:mass(_mass), color(_color)
		{

		}
		float mass;
		Color color;
	};
}
