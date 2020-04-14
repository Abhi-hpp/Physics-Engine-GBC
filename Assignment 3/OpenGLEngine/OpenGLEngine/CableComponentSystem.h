#pragma once
#include "ECSConfig.h"
#include "CableComponent.h"
namespace Reality
{
	class CableComponentSystem : public ECSSystem
	{
	public:
		CableComponentSystem();
		void Update(float deltaTime);
	};
}

