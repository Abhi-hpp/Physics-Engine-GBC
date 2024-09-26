#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponent.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);

		float waterHeight;
		Vector3 liquidVolume;
		float liquidDensity;
	};
}
