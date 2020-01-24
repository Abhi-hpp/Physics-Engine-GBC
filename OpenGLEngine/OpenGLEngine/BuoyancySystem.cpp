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
			auto& entityForceAcc = e.getComponent<ForceAccumulatorComponent>();

			float depth = entityTransform.position.y;

			//Draw cube
			getWorld().data.renderUtil->DrawCube(
				entityTransform.position,
				Vector3(entityBuoyancy.maxDepth * 2.f, entityBuoyancy.maxDepth * 2.f, entityBuoyancy.maxDepth * 2.f),
				Vector3(0, 0, 0));

			//Draw water surface
			getWorld().data.renderUtil->DrawLine(Vector3(-50, 0, -5), Vector3(50, 0, 5));

			//check if entity is out of water
			if (depth >= waterHeight + entityBuoyancy.maxDepth)
			{
				return;
			}

			Vector3 force = Vector3(0.f, 0.f, 0.f);

			////check if entity is at maximum depth
			if (depth <= waterHeight - entityBuoyancy.maxDepth)
			{
				force.y = liquidDensity * entityBuoyancy.volume;
				entityForceAcc.AddForce(force);
				return;
			}

			//otherwise entity is partly submerged
			force.y = liquidDensity * entityBuoyancy.volume * (entityBuoyancy.maxDepth - depth - waterHeight) / 2 * entityBuoyancy.maxDepth;
			//force.y = (entityBuoyancy.maxDepth - depth - waterHeight) / 2 * entityBuoyancy.maxDepth;
			entityForceAcc.AddForce(force);
		}
	}
}
