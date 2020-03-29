#pragma once
#include "ECSConfig.h"
#include "AeroComponent.h"

namespace Reality
{
	struct RigidBodyComponent;
	struct TransformComponentV2;
	class AeroSystem : public ECSSystem
	{
	public:
		AeroSystem();
		void Update(float deltaTime);
		Vector3 windspeed = Vector3(0, 0, 0);
	private:
		void UpdateForceFromTensor(ECSWorld& world, AeroComponent& aero, RigidBodyComponent& body, TransformComponentV2& transform);
	};
}
