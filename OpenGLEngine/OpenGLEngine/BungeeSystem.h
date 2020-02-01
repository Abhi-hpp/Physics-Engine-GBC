#pragma once
#include "ECSConfig.h"
#include "BungeeComponent.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class BungeeSystem : public ECSSystem
	{
	public:
		BungeeSystem();
		void Update(float deltaTime);
	};
}
