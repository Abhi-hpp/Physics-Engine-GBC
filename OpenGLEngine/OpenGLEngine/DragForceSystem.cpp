#include "DragForceSystem.h"

namespace Reality
{
	DragForceSystem::DragForceSystem()
	{
		requireComponent<DragForceComponent>();
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<ParticleComponent>();
	}

	void DragForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& drag = e.getComponent<DragForceComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto& particle = e.getComponent<ParticleComponent>();
			
			Vector3 vel = particle.velocity;
			float velocityMagnitude = glm::length(vel);

			if (velocityMagnitude > 0)
			{
				Vector3 dragForce = -glm::normalize(particle.velocity) * (drag.k1 * velocityMagnitude + drag.k2 * pow(velocityMagnitude, 2));
				forceAcc.AddForce(dragForce);
			}
		}
	}
}
