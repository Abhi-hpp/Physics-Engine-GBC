#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);
		Vector3 liquidFloorDimensions = Vector3(200, 15, 200); // size of the liquid floor
	};
}
