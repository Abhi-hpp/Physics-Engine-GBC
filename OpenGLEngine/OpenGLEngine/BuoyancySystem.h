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
		float waterHeight = 5.0f;
		float liquidDensity = 10.0f;
	};
}
