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
		// how large the water volume is that the objects interact with
		Vector3 waterDimensions = Vector3(50, 50, 50);
	};
}
