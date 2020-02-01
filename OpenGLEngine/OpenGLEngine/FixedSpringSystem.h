#pragma once
#include "ECSConfig.h"
#include "FixedSpringComponent.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class FixedSpringSystem : public ECSSystem
	{
	public:
		FixedSpringSystem();
		void Update(float deltaTime);
	};
}
