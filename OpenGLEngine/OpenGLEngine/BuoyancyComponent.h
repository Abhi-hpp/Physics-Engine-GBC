#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(Vector3 _dimensions = Vector3(1.0,1.0,1.0),
			float _waterHeight = 0.0f, float _liquidDenisty = 1000)
			:dimensions(_dimensions), waterHeight(_waterHeight), liquidDensity(_liquidDenisty)
		{

		}

		// using this to allow for custom dimensions of the buuoyancy component
		Vector3 dimensions;

		float waterHeight;

		float liquidDensity;



	};
}
