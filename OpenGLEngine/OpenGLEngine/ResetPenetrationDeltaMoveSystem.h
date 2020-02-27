#pragma once
#include "ECSConfig.h"
#include "PenetrationDeltaMoveComponent.h"

namespace Reality
{
	class ResetPenetrationDeltaMoveSystem : public ECSSystem
	{
	public:
		ResetPenetrationDeltaMoveSystem();
		void Update(float deltaTime);
	};
}
