#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class BuoyancyForceSystem : public ECSSystem
	{
	public:
		BuoyancyForceSystem();
		void Update(float deltaTime);
		static float liquidDensity;
	};
}
