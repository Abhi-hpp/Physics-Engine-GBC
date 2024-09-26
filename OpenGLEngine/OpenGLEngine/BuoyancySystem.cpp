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
			//Draw water surface
			getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -5), Vector3(500, 0, 5));


			auto& entityTransform = e.getComponent<TransformComponent>();
			auto& entityBuoyancy = e.getComponent<BuoyancyComponent>();
			auto& entityForceAcc = e.getComponent<ForceAccumulatorComponent>();

			float depth = entityTransform.position.y;

			//Draw cube
			getWorld().data.renderUtil->DrawCube(
				entityTransform.position,
				Vector3(entityBuoyancy.maxBuoyancyDepth * 2.f, entityBuoyancy.maxBuoyancyDepth * 2.f, entityBuoyancy.maxBuoyancyDepth * 2.f),
				Vector3(0, 0, 0));

			Vector3 force = Vector3(0.f, 0.f, 0.f);

			//check if entity is out of water
			if (depth >= waterHeight + entityBuoyancy.maxBuoyancyDepth)
			{
				force.y = 0.f;
			}

			//check if entity is at maximum depth
			else if (depth <= waterHeight - entityBuoyancy.maxBuoyancyDepth)
			{
				force.y = liquidDensity * entityBuoyancy.buoyancyVolume;
			}

			//otherwise entity is partly submerged
			else
			{
				force.y = (liquidDensity * entityBuoyancy.buoyancyVolume * (entityBuoyancy.maxBuoyancyDepth - depth - waterHeight)) / (2 * entityBuoyancy.maxBuoyancyDepth);
			}

			entityForceAcc.AddForce(force);
		}
	}
}
