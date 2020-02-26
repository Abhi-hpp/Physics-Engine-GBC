#pragma once
#include "ECSConfig.h"
#include "CableComponent.h"

namespace Reality
{
	class CableSystem : public ECSSystem
	{
	public:
		CableSystem();
		void Update(float deltaTime);
	};
}
