#pragma once
#include "ECSConfig.h"
#include "FloorCollideComponent.h"
#include "ParticleSphereComponent.h"

namespace Reality
{
	class FloorCollideSystem : public ECSSystem
	{
	public:
		FloorCollideSystem();
		void Update(float deltaTime);
	};
}
