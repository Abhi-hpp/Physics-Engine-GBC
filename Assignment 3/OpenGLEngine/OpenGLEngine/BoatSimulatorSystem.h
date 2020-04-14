#pragma once
#include "ECSConfig.h"
#include "BoatSimulatorComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class BoatSimulatorSystem : public ECSSystem
	{
	public:
		BoatSimulatorSystem();
		void Update(float deltaTime);
	private:
		float movement = 0;
	};
}
