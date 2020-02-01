#include "BuoyantSpringSystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BuoyantSpringSystem::BuoyantSpringSystem()
	{
		requireComponent<BuoyantSpringComponent>();
	}

	void BuoyantSpringSystem::Update(float deltaTime)
	{


		for (auto e : getEntities())
		{
			auto& entityTransform = e.getComponent<TransformComponent>();
			auto& entityBuoyant = e.getComponent<BuoyantSpringComponent>();
			auto& entityForceAcc = e.getComponent <ForceAccumulatorComponent>();

			int i = 0;
			i++;

			getWorld().data.renderUtil->DrawCube(Vector3(0, -5, 50), Vector3(200, 10, 400));




			float depth = entityTransform.position.y;

			getWorld().data.renderUtil->DrawCube(entityTransform.position,
				Vector3(entityBuoyant.maxDepth * 2.0f, entityBuoyant.maxDepth * 2.0f, entityBuoyant.maxDepth * 2.0f),
				Vector3(0, 0, 0));

			Vector3 force = Vector3(0.0f, 0.0f, 0.0f);

			if (depth >= height + entityBuoyant.maxDepth)
			{
				force.y = 0.0f;
			}
			else if (depth <= height - entityBuoyant.maxDepth)
			{
				force.y = density * entityBuoyant.volume;
			}
			else
			{
				force.y = density * entityBuoyant.volume * (entityBuoyant.maxDepth - depth - height);
			}

			entityForceAcc.AddForce(force);
		}
	}
}
