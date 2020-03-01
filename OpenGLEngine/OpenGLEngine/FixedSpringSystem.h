#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "FixedSpringComponent.h"

namespace Reality
{
	class FixedSpringSystem : public ECSSystem
	{
	public:
		FixedSpringSystem();
		void Update(float deltaTime);
	};
}
