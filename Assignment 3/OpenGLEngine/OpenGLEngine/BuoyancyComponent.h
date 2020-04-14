#pragma once
#include "RigidbodyGravityForceGeneratorSystem.h"
#include "ECSConfig.h"

namespace Reality {

	struct BuoyancyComponent
	{
	public:

		BuoyancyComponent(float _maxDepth = 100, float _volume = 1000, float _waterHeight = 450, float _liquidDensity = 0.8f):
			maxDepth(_maxDepth), volume(_volume), waterHeight(_waterHeight), liquidDensity(_liquidDensity)
		{

		}

		// when max depth of water
		float maxDepth;
		
		// volum of the water
		float volume;

		// hight of the water surface
		float waterHeight;
		
		// density of the water
		float liquidDensity;

	};
}

