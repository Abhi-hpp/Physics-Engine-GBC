#include "BuoyancySystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BuoyancyComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& entityTransform = e.getComponent<TransformComponent>();
			auto& entityBuoyancy = e.getComponent<BuoyancyComponent>();

			float depth = entityTransform.position.y;

			//check if entity is out of water
			if (depth >= waterHeight + entityBuoyancy.maxDepth)
			{
				return;
			}

			//check if entity is at maximum depth
			if (depth <= waterHeight - entityBuoyancy.maxDepth)
			{

			}
		}
	}
}
