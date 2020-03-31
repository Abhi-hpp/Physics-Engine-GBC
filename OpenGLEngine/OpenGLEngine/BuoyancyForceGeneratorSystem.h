#pragma once
#include "ECSConfig.h"
#include "BuoyancyForceGeneratorComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class BuoyancyForceGeneratorSystem : public ECSSystem
	{
	public:
		BuoyancyForceGeneratorSystem();
		void Update(float deltaTime);
	};
}
