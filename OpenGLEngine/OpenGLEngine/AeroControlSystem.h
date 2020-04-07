#pragma once
#include "ECSConfig.h"
#include "AeroSurfaceComponent.h"
#include "AeroControlComponent.h"

namespace Reality
{
	class AeroControlSystem : public ECSSystem
	{
	public:
		AeroControlSystem();
		void Update(float deltaTime);
	};
}
