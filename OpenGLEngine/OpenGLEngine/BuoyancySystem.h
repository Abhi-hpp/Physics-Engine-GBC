#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "BuoyancyComponent.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);

		float waterHeight = 0.f;
		float liquidDensity = 1.f;
	};
}

