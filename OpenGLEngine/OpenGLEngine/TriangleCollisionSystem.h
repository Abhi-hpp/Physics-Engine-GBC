#pragma once
#include "ECSConfig.h"
#include "ParticleSphereComponent.h"
#include "TriangleCollisionComponent.h"

namespace Reality
{
	class TriangleCollisionSystem : public ECSSystem
	{
	public:
		TriangleCollisionSystem();
		void Update(float deltaTime);
	private:
	};
}
