#include "BuoyancySystem.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<ParticleComponent>();
		requireComponent<TransformComponent>();
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<BuoyancyComponent>();
	}

	float BuoyancySystem::liquidDensity = 50.0f;

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& buoy = e.getComponent<BuoyancyComponent>();
			auto& transform = e.getComponent<TransformComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			Vector3 force(0, 1, 0);

			// ------ this is DEPTH ------------ //
			float d = ((buoy.maxDepth / 2) - (transform.position.y - waterVolume.y)) / buoy.maxDepth;

			if (d >= buoy.maxDepth)
			{
				force.y = liquidDensity * buoy.volume;
			}
			else
			{
				float depthR = d / buoy.maxDepth;

				force.y = liquidDensity * depthR * buoy.volume;
			}
			forceAcc.AddForce(force);
		}
		//getWorld().data.renderUtil->DrawCube(Vector3(0, 0, 0), Vector3(200, 200, 200), Vector3(0, 0, 0), Color::Orange);
	}
}
