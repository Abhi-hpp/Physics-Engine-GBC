#pragma once
#include "ECSConfig.h"
#include "BuoyancyControlEvent.h"
#include "BuoyancySystem.h"

namespace Reality
{
	class BuoyancyControlSystem : public ECSSystem
	{
	public:
		BuoyancyControlSystem();
		void Update(float deltaTime);
	private:
		bool spacePressed = false;
		bool plusPressed = false;
		bool minusPressed = false;
	};
}
