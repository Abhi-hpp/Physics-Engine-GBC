#pragma once
#include "ECSConfig.h"
//#include "ForceAccumulatorComponent.h"
#include "FixedSpringComponent.h"
#include "TransformComponent.h"


namespace Reality
{
	class FixedSpringSystem : public ECSSystem
	{
	public:
		FixedSpringSystem();
		void Update(float deltaTime);
	};
}
