#pragma once
#include "ECSConfig.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"

namespace Reality
{
	class GravityForceSystem : public ECSSystem
	{
	public:
		GravityForceSystem();
		void Update(float deltaTime);
		Vector3 worldGravity = Vector3(0.0f, -9.8f, 0.0f);
	};
}
