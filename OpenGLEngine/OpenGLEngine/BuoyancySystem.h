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

		bool spawning = true;
		float currentBuoyancyValue;
		float width = 50;
		float length = 50;
	};
}
