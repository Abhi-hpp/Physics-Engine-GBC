#pragma once
#include "ECSConfig.h"
#include "FPSControlComponent.h"

namespace Reality
{
	class FPSControlSystem : public ECSSystem
	{
	public:
		FPSControlSystem();
		void Update(float deltaTime);
	};
}

