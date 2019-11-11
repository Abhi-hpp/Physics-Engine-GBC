#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "FixedSpringComponent.h"

namespace Reality
{
	class FixedSpringForceGeneratorSystem : public ECSSystem
	{
	public:
		FixedSpringForceGeneratorSystem();
		void Update(float deltaTime);
	};
}

