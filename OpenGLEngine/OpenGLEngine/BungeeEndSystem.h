#pragma once
#include "ECSConfig.h"
#include "BungeeEndComponent.h"

namespace Reality
{
	class BungeeEndSystem : public ECSSystem
	{
	public:
		BungeeEndSystem();
		void Update(float deltaTime);
	private:
		bool spacePressed = false;
	};
}
