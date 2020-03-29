#pragma once
#include "RigidbodyGravityForceGeneratorSystem.h"
#include "ECSConfig.h"

namespace Reality {

	struct BuoyancyComponent
	{
	public:

		BuoyancyComponent(const Vector3& _center = Vector3(0,0,0), float _maxDepth = 100, float _volume = 1000, float _waterHeight = 450, float _liquidDensity = 0.8f):
			maxDepth(_maxDepth), volume(_volume), waterHeight(_waterHeight), liquidDensity(_liquidDensity), centerOfBuoyancy(_center)
		{

		}
		float GetWaterHeight()
		{
			return waterHeight;
		}
		float GetLiquidDensity()
		{
			return liquidDensity;
		}
	private:

		// when sumbmerged to maxDepth buoyancy force is at maximum
		float maxDepth;
		
		// volum of the object
		float volume;

		// hight of the water surface
		float waterHeight;
		
		// density
		float liquidDensity;

		// center of the force
		Vector3 centerOfBuoyancy;

	};
}

