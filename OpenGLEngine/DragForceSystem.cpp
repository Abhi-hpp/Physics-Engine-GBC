#include "DragForceSystem.h"

namespace Reality
{
	DragForceSystem::DragForceSystem()
	{
		requireComponent<ParticleComponent>();
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<DragForceComponent>();
	}

	void DragForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& particle = e.getComponent<ParticleComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto& drag = e.getComponent<DragForceComponent>();

			float speed = glm::length(particle.velocity);
			if (speed > 0)
			{
				Vector3 force = -glm::normalize(particle.velocity);
				force *= drag.k1 * speed + drag.k2 * pow(speed, 2);
				forceAcc.AddForce(force);
			}
		}
	}
}
