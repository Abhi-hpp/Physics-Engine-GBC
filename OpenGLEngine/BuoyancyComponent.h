#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(Vector3 _dimensions = Vector3(1,1,1), float _liquidHeight = 0.0f, float _liquidDenisty = 1000)
			:dimensions(_dimensions), liquidHeight(_liquidHeight), liquidDensity(_liquidDenisty)
		{

		}

		Vector3 dimensions;
		float liquidHeight;
		float liquidDensity;
	};
}
