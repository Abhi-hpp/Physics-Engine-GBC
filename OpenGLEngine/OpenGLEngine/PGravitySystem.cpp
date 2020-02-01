#include "PGravitySystem.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	PGravitySystem::PGravitySystem()
	{
		requireComponent<PGravityComponent>();
		requireComponent<TransformComponent>();
	}

	void PGravitySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& ForceAcc = e.getComponent<ForceAccumulatorComponent>();

			if (e.hasComponent<PGravityComponent>())
			{
				for (auto obj : getEntities())
				{
					auto& ForceAcc2 = obj.getComponent<ForceAccumulatorComponent>();
					if (obj.hasComponent<PGravityComponent>() && obj != e)
					{
						glm::vec3 Length = obj.getComponent<TransformComponent>().position - e.getComponent<TransformComponent>().position;
						float force = 3.0f * (ForceAcc.mass * ForceAcc2.mass) / glm::length(Length);
						glm::vec3 dir = glm::normalize(Length);

						ForceAcc.AddForce(force * dir);
					}
				}

			}
		}
	}
}
