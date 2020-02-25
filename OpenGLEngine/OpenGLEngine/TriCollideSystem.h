#pragma once
#include "ECSConfig.h"
#include "TriCollideComponent.h"
#include "ParticleSphereComponent.h"

namespace Reality
{
	class TriCollideSystem : public ECSSystem
	{
	public:
		TriCollideSystem();
		void Update(float deltaTime);
	};
}
