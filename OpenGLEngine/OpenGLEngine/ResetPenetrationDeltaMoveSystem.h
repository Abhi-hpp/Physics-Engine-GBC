#pragma once
#include "ECSConfig.h"

namespace Reality
{
	class ResetPenetrationDeltaMoveSystem : public ECSSystem
	{
	public:
		ResetPenetrationDeltaMoveSystem();
		void Update(float deltaTime);
	};
}
