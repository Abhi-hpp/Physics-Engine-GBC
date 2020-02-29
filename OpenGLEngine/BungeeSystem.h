#pragma once
#include "ECSConfig.h"
#include "BungeeComponent.h"

namespace Reality
{
	class BungeeSystem : public ECSSystem
	{
	public:
		BungeeSystem();
		void Update(float deltaTime);
	};
}
