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

		Vector3 liquidVolume = Vector3(0, 0, 0);
		float liquidDensity = 0.05f;
	};
}
