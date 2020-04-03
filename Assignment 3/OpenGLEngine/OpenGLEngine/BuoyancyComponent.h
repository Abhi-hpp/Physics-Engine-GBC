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

		// when sumbmerged to maxDepth buoyancy force is at maximum
		float maxDepth;
		
		// volum of the object
		float volume;

		// hight of the water surface
		float waterHeight;
		
		// density
		float liquidDensity;

	};
}

