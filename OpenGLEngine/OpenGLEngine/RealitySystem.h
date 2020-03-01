#pragma once
#include "ECSConfig.h"

namespace Reality
{
	class RealitySystem : public ECSSystem
	{
	public:
		RealitySystem();
		void Update(float deltaTime);
	};
}
