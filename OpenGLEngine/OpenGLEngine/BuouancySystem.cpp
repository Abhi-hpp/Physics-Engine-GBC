#include "BuouancySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"


namespace Reality
{
	BuouancySystem::BuouancySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BuoyancyComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void BuouancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& PTransform = e.getComponent<TransformComponent>();
			auto& PBuoyancy = e.getComponent<BuoyancyComponent>();
			auto& PForceAcc = e.getComponent<ForceAccumulatorComponent>();

			float depth = PTransform.position.y;

			if (depth >= PBuoyancy.waterHeight + PBuoyancy.maxDepth)
			{
				return;
			}
			Vector3 force(0, 0, 0);

			if (depth <= PBuoyancy.waterHeight - PBuoyancy.maxDepth)
			{
				force.y = PBuoyancy.liquidDensity * PBuoyancy.volume;
				PForceAcc.AddForce(force);
				return;
			}

			force.y = PBuoyancy.liquidDensity * PBuoyancy.volume * (depth - PBuoyancy.maxDepth - PBuoyancy.waterHeight) / 2 * PBuoyancy.maxDepth;
			PForceAcc.AddForce(force);

		}
	}
}
