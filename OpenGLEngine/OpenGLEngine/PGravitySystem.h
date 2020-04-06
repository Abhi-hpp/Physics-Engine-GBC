#pragma once
#include "ECSConfig.h"
#include "PGravityComponent.h"

namespace Reality
{
	class PGravitySystem : public ECSSystem
	{
	public:
		PGravitySystem();
		void Update(float deltaTime);
	};
}
