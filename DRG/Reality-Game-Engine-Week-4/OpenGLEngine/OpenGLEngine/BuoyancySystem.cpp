#include "BuoyancySystem.h"
#include "TransformComponent.h"
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
			auto& spring = e.getComponent<BuoyancyComponent>();

			if (spring.connectedEntityA.hasComponent<TransformComponent>())
			{
				auto& transformA = spring.connectedEntityA.getComponent<TransformComponent>();

				float depth = transformA.position.y;

				if (depth >= spring.waterHeight + spring.maxDepth)
				{
					return;
				}

				Vector3 force(0, 0, 0);

				if (depth <= spring.waterHeight - spring.maxDepth)
				{
					force.y = spring.liquidDensity * spring.volume;
					spring.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					return;
				}

				else {
					force.y = spring.liquidDensity * spring.volume * (depth - spring.maxDepth - spring.waterHeight) / 2 * spring.maxDepth;
					spring.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
				}

			}
		}
	}
}
