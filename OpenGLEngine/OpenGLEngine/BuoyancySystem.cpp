#include "BuoyancySystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& forceAccumulator = e.getComponent <ForceAccumulatorComponent>();
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			
			getWorld().data.renderUtil->DrawCube(transform.position, Vector3(15.0f, 15.0f, 15.0f), Vector3(0, 0, 0),Color::Blue);
			
			// Calculate the submersion depth
			float depth = transform.position.y;
			Vector3 force = Vector3(0.0f, 0.0f, 0.0f);

			// Check if we're out of the water
			if (depth >= waterHeight + buoyancy.maxDepth)
				return;
			// Check if we're at maximum depth
			else if (depth <= waterHeight - buoyancy.maxDepth)
			{
				force.y = liquidDensity * buoyancy.volume;
				forceAccumulator.AddForce(force);
			}
			// Otherwise we're partly submerged
			else
			{
				force.y = liquidDensity * buoyancy.volume * (buoyancy.maxDepth - depth - waterHeight) / 2 * buoyancy.maxDepth;
				forceAccumulator.AddForce(force);
			}
		}
	}
}
