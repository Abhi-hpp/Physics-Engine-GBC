#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "ParticleSpawnerComponent.h"

namespace Reality
{
	class ParticleSpawnerSystem : public ECSSystem
	{
	public:
		ParticleSpawnerSystem();
		void Update(float deltaTime);
	};
}

