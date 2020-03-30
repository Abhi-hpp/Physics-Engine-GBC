#pragma once
#include "ECSConfig.h"
#include "BuoyancyGeneratorComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class BuoyancyGeneratorSystem : public ECSSystem
	{
	public:
		BuoyancyGeneratorSystem();
		void Update(float deltaTime);
	};
}
