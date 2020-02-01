#include "BuoyancySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

// Equations taken from Game Physics Engine Development textbook.

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& transform = e.getComponent<TransformComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			// Cube (water visualization)
			getWorld().data.renderUtil->DrawCube(Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, buoyancy.maxDepth, 50.0f), Vector3(0.0f ,0.0f ,0.0f), Color::Blue);

			// Cube (object visualization)
			getWorld().data.renderUtil->DrawCube(transform.position, Vector3(2.0f, 2.0f, 2.0f), Vector3(1.0f, 1.0f, 1.0f), Color::Red);

			// Calculate the submersion depth.
			float depth = transform.position.y;

			// Check if out of water.
			if (depth >= buoyancy.waterHeight + buoyancy.maxDepth)
			{
				return;
			}

			Vector3 force = Vector3(0.0f, 0.0f, 0.0f);

			// Check if at maximum depth.
			if (depth <= buoyancy.waterHeight - buoyancy.maxDepth)
			{
				force.y = buoyancy.liquidDensity * buoyancy.volume;
				forceAcc.AddForce(force);
			}
			else // Otherwise partly submerged.
			{
				force.y = (buoyancy.liquidDensity * buoyancy.volume * (buoyancy.maxDepth - depth - buoyancy.waterHeight)) / (2 * buoyancy.maxDepth);
				//force.y = (buoyancy.liquidDensity * buoyancy.volume * (depth - buoyancy.maxDepth - buoyancy.waterHeight) / (2 * buoyancy.maxDepth)); // This is what is described in the book, however, this does not seem to work properly.
				forceAcc.AddForce(force);
			}
		}
	}
}