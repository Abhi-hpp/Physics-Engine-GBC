#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _mass = 5.0f, float _gVariable = 5.0f) : mass(_mass),
			gVariable(_gVariable)
		{

		}

		float mass;
		float gVariable;
	};
}
