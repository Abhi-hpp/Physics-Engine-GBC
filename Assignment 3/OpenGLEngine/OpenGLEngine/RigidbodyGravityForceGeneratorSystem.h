#pragma once
#include "ECSConfig.h"
#include "RigidBodyComponent.h"

namespace Reality
{
	class RigidbodyGravityForceGeneratorSystem : public ECSSystem
	{
	public:
		Vector3 gravity = Vector3(0.0f, -9.8f, 0.0f);
		RigidbodyGravityForceGeneratorSystem();
		void Update(float deltaTime);
	};
}
