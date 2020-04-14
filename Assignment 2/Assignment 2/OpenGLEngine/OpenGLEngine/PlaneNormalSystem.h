#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "PlaneNormalComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class PlaneNormalSystem : public ECSSystem
	{
	public:
		PlaneNormalSystem();
		void Update(float deltaTime);
	};
}
