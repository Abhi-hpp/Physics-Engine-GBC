#pragma once
#include "ECSConfig.h"
#include "ParticleComponent.h"

namespace Reality
{
	class GravityForceGeneratorSystem : public ECSSystem
	{
	public:
		Vector3 gravity = Vector3(0, -9.8f, 0);
		GravityForceGeneratorSystem();
		void Update(float deltaTime);
	};
}

