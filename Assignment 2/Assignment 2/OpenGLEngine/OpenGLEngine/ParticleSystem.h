#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"

namespace Reality
{
	class ParticleSystem : public ECSSystem
	{
	public:
		ParticleSystem();
		void Update(float deltaTime);
	};
}
