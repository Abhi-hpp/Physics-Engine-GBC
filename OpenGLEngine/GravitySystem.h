#pragma once
#include "ECSConfig.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "GravityComponent.h"

namespace Reality
{
	class GravitySystem : public ECSSystem
	{
	public:
		GravitySystem();
		void Update(float deltaTime);
		Vector3 worldGravity = Vector3(0.0f, -9.8f, 0.0f);
	};
}
