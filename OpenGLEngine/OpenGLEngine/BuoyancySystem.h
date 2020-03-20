#pragma once
#include "ECSConfig.h"
#include "Buoyancy.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);
	};
}
