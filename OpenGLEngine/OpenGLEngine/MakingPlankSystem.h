#pragma once
#include "ECSConfig.h"
#include "MakingPlankComponent.h"

namespace Reality
{
	class MakingPlankSystem : public ECSSystem
	{
	public:
		MakingPlankSystem();
		void Update(float deltaTime);
	};
}
