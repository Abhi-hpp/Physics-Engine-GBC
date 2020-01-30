#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "BuoyantSpringComponent.h"

namespace Reality
{
	class BuoyantSpringSystem : public ECSSystem
	{
	public:
		BuoyantSpringSystem();
		void Update(float deltaTime);
	};
}
