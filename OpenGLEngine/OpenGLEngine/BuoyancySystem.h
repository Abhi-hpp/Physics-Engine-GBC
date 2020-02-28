#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "BuoyancyComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);

		float density = 1000.0f;
	};
}
