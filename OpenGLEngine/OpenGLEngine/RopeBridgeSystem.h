#pragma once
#include "ECSConfig.h"
#include "RopeBridgeComponent.h"

namespace Reality
{
	class RopeBridgeSystem : public ECSSystem
	{
	public:
		RopeBridgeSystem();
		void Update(float deltaTime);
	};
}
