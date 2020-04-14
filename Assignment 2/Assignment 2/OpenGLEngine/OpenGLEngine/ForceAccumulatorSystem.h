#pragma once
#include "ECSConfig.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class ForceAccumulatorSystem : public ECSSystem
	{
	public:
		ForceAccumulatorSystem();
		void Update(float deltaTime);
	};
}
