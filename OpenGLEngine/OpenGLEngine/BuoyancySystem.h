#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponent.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);
	private:
		bool createBox = false;
		ECSEntity boundingBox;
		bool insindeWater = false;
		bool stopMoving = false;
	};
}
