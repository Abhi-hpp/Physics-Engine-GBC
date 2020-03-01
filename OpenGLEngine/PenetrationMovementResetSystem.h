#pragma once
#include "ECSConfig.h"
#include "PenetrationMovementComponent.h"

namespace Reality
{
	class PenetrationMovementResetSystem : public ECSSystem
	{
	public:
		PenetrationMovementResetSystem();
		void Update(float deltaTime);
	};
}
