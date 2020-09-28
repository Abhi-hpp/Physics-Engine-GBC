#pragma once
#include "ECSConfig.h"
#include "GravityForceComponentV2.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	class GravityForceSystemV2 : public ECSSystem
	{
	public:
		GravityForceSystemV2();
		void Update(float deltaTime);

		Vector3 worldGravity = Vector3(0.0f, -9.8f, 0.0f);
	};
}
