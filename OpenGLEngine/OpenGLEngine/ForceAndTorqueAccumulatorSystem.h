#pragma once
#include "ECSConfig.h"
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class ForceAndTorqueAccumulatorSystem : public ECSSystem
	{
	public:
		ForceAndTorqueAccumulatorSystem();
		void Update(float deltaTime);
	};
}
