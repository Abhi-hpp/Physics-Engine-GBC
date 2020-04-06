#pragma once
#include "ECSConfig.h"
#include "ParticleComponent.h"

namespace Reality
{
	class ForceAccumulatorSystem : public ECSSystem
	{
	public:
		ForceAccumulatorSystem();
		void Update(float deltaTime);
	};
}

