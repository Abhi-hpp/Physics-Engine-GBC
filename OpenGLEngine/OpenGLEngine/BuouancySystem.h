#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponent.h"

namespace Reality
{
	class BuouancySystem : public ECSSystem
	{
	public:
		BuouancySystem();
		void Update(float deltaTime);
	};
}
