#include "DragForceSystem.h"
#include "ParticleComponent.h"

namespace Reality
{
	DragForceSystem::DragForceSystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<DragForceComponent>();
	}

	void DragForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto velocity = e.getComponent<ParticleComponent>().velocity;
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto drag = e.getComponent<DragForceComponent>();

			if (glm::length(velocity) > 0) // Non-Zero Vector
			{
				auto force = (-glm::normalize(velocity)) *
					((drag.k1 * glm::length(velocity)) + (drag.k2 * glm::length(velocity) * glm::length(velocity)));
				forceAcc.AddForce(force);
			}
		}
	}
}
