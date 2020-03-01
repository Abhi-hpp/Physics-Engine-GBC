#pragma once
#include "ECSConfig.h"
#include "BridgeRopeComponent.h"

namespace Reality
{
	class BridgeRopeSystem : public ECSSystem
	{
	public:
		BridgeRopeSystem();
		void Update(float deltaTime);
	};
}
