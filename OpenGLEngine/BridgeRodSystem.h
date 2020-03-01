#pragma once
#include "ECSConfig.h"
#include "BridgeRodComponent.h"

namespace Reality
{
	class BridgeRodSystem : public ECSSystem
	{
	public:
		BridgeRodSystem();
		void Update(float deltaTime);
	};
}
