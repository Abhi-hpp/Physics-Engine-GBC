#pragma once
#include "ECSConfig.h"
#include "FlighSimulatorComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class FlightSimulatorSystem : public ECSSystem
	{
	public:
		FlightSimulatorSystem();
		void Update(float deltaTime);
	private:
		float timer = 0;
	};
}
