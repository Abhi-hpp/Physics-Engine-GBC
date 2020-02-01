#include "BuoyancySystem.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<TransformComponent>();
		requireComponent<BuoyancyComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{

			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto& transf = e.getComponent<TransformComponent>();
			auto& bouy = e.getComponent<BuoyancyComponent>();

			getWorld().data.renderUtil->DrawLine(Vector3(-1000, 0, -5), Vector3(1000, 0, 5), Color::Blue);
			getWorld().data.renderUtil->DrawCube(
				transf.position, Vector3(bouy.maxDepth * 2.0f, bouy.maxDepth * 2.0f, bouy.maxDepth * 2.0f),
				Vector3(0, 0, 0), Color::Red);

			// Calculate the submersion depth.
			float depth = transf.position.y;

			// Check if we’re out of the water.
			if (depth >= bouy.waterHeight + bouy.maxDepth) return;
			Vector3 force(0, 0, 0);

			// Check if we’re at maximum depth.
			if (depth <= bouy.waterHeight - bouy.maxDepth)
			{
				force.y = bouy.liquidDensity * bouy.volume;
				forceAcc.AddForce(force);
				return;
			}
			
			// Otherwise we are partly submerged.
			force.y = (bouy.liquidDensity * bouy.volume *
				(depth - bouy.maxDepth - bouy.waterHeight)) / 2 * bouy.maxDepth;
			forceAcc.AddForce(force);
			
		}
	}
}
