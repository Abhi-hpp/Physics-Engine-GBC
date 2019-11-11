#pragma once
#include "ECSConfig.h"
#include "RigidBodyComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class RigidBodySystem : public ECSSystem
	{
	public:
		RigidBodySystem();
		void Update(float deltaTime);
	};
}
