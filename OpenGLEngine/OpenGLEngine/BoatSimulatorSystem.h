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
		float timer = 0;
		float i = 0;
		Reality::Vector3 rad = glm::vec3(
			glm::radians(0.0f),
			glm::radians(0.0f),
			glm::radians(0.0f)
		);
	};
}
