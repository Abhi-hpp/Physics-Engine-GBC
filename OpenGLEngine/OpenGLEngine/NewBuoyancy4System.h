#pragma once
#include "ECSConfig.h"

namespace Reality
{
	class NewBuoyancy4System : public ECSSystem
	{
	public:
		NewBuoyancy4System();
		void Update(float deltaTime);
		float UpForce(float depth, float vol);
		float liquidDensity = 10.5f;
		float waterLevel = 0.0f;
	};
}
