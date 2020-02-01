#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "BuoyancyComponent.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);

		Vector3 waterVolume = { 100, 100, 100 };
		static float liquidDensity;

	};

}
