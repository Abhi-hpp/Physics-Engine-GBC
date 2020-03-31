#pragma once
#include "ECSConfig.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "DragForceComponent.h"

namespace Reality
{
	class DragForceSystem : public ECSSystem
	{
	public:
		DragForceSystem();
		void Update(float deltaTime);
	};
}
