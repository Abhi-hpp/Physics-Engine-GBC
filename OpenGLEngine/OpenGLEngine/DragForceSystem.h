#pragma once
#include "ECSConfig.h"
#include "DragForceComponent.h"
#include "ForceAccumulatorComponent.h"
#include "ParticleComponent.h"

namespace Reality
{
	class DragForceSystem : public ECSSystem
	{
	public:
		DragForceSystem();
		void Update(float deltaTime);
	};
}
