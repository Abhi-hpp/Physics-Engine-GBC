#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "AddTorqueFromCameraComponent.h"

namespace Reality
{
	class AddTorqueFromCameraSystem : public ECSSystem
	{
	public:
		AddTorqueFromCameraSystem();
		void Update(float deltaTime);
	private:
		bool pressed = false;
	};
}
