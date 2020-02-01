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

		float height = 0.0f;
		float density = 10.0f;
	};
}
