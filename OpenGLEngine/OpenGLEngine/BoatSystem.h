#pragma once
#include "ECSConfig.h"
#include "BoatComponent.h"

namespace Reality
{
	class BoatSystem : public ECSSystem
	{
	public:
		BoatSystem();
		void Update(float deltaTime);
	};
}
