#pragma once
#include "ECSConfig.h"
<<<<<<< Updated upstream
#include "RigidBodyComponent.h"
=======
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"
>>>>>>> Stashed changes
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
