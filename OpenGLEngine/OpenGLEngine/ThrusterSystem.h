#pragma once
#include "ECSConfig.h"
#include "ThrusterComponent.h"

namespace Reality
{
	class ThrusterSystem : public ECSSystem
	{
	public:
		ThrusterSystem();
		void Update(float deltaTime);
	};
}
