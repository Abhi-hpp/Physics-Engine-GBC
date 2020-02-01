#pragma once
#include "ECSConfig.h"

// NOTE: Even when putting liquidDensity = 1000.0f, certain values do not seem to be properly/realistically calculated.
// Placeholder values of 10.0f are inserted into everything as a result.

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 10.0f, float _volume = 10.0f, float _waterHeight = 1.0f, float _liquidDensity = 10.0f)
			: maxDepth(_maxDepth), volume(_volume), waterHeight(_waterHeight), liquidDensity(_liquidDensity)
		{

		}
		float maxDepth; // The maximum submersion depth of the object.
		float volume; // Volume of the object.
		float waterHeight; // Height of the water plane.
		float liquidDensity; // Density of the liquid.
	};
}