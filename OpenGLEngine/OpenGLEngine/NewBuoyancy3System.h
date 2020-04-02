#pragma once
#include "ECSConfig.h"

namespace Reality
{
	class NewBuoyancy3System : public ECSSystem
	{
	public:
		NewBuoyancy3System();
		void Update(float deltaTime);
		float UpForce(float depth, float vol);
		float liquidDensity = 10.5f;
		float waterLevel = 0.0f;
	};
}
