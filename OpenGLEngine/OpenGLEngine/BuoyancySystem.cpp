#include "BuoyancySystem.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponent>();
		requireComponent<ForceAccumulatorComponent>();

		waterHeight = 0;
		liquidVolume = Vector3(100, 0, 100);
		liquidDensity = 50;
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		if (DEBUG_LOG_LEVEL > 0)
			getWorld().data.renderUtil->DrawCube(Vector3(0, waterHeight, 0), liquidVolume, Vector3(0, 0, 0), Color::Cyan);

		for (auto e : getEntities())
		{
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& transform = e.getComponent<TransformComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			if (DEBUG_LOG_LEVEL > 0)
				getWorld().data.renderUtil->DrawCube(transform.position, buoyancy.cubeScale, Vector3(0, 0, 0), Color::Orange);

			float edge = liquidVolume.x / 2;

			if (transform.position.x >= -edge && transform.position.x <= edge && transform.position.z >= -edge && transform.position.z <= edge)
			{
				float depth = transform.position.y;

				if (depth >= waterHeight + buoyancy.maxDepth)
					return;

				Vector3 force(0, 0, 0);

				if (depth <= waterHeight - buoyancy.maxDepth)
				{
					force.y = liquidDensity * buoyancy.volume;
					forceAcc.AddForce(force);
					return;
				}

				float d = abs((depth - buoyancy.maxDepth - waterHeight) / (4 * buoyancy.maxDepth));

				force.y = liquidDensity * buoyancy.volume * d;// (depth - buoyancy.maxDepth - waterHeight) / 2 * buoyancy.maxDepth;
				forceAcc.AddForce(force);
			}
		}
	}
}
