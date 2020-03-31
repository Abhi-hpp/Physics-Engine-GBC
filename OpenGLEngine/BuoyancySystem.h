#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponent.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);

		Vector3 liquidVolume = Vector3(0, 0, 0);
		float liquidDensity = 0.90f;
	};
}
