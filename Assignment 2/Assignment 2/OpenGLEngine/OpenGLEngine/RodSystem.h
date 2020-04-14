#pragma once
#include "ECSConfig.h"
#include "RodComponent.h"

namespace Reality
{
	class RodSystem : public ECSSystem
	{
	public:
		RodSystem();
		void Update(float deltaTime);
	};
}
