#pragma once
#include "ECSConfig.h"
#include "WindThrusterComponent.h"

namespace Reality
{
	class WindThrusterSystem : public ECSSystem
	{
	public:
		WindThrusterSystem();
		void Update(float deltaTime);
	};
}
