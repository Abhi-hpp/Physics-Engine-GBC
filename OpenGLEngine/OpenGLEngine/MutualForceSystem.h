#pragma once
#include "ECSConfig.h"
#include "ForceAccumulatorComponent.h"
#include "MutualForceComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class MutualForceSystem : public ECSSystem
	{
	public:
		MutualForceSystem();
		void Update(float deltaTime);

	private:
		void CalculateMutualForce(ECSEntity &contact, ECSEntity &contact2);
	};
}
