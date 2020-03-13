#include "DragForceSystem.h"

namespace Reality
{
	DragForceSystem::DragForceSystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<ParticleComponent>();
		requireComponent<DragForceComponent>();
	}

	void DragForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto& particle = e.getComponent<ParticleComponent>();
			auto& drag = e.getComponent<DragForceComponent>();

			float velocityMag = glm::length(particle.velocity);
			if (velocityMag > 0)
			{
				Vector3 force = -glm::normalize(particle.velocity);
				force *= drag.k1 * velocityMag + drag.k2 * pow(velocityMag, 2);

				forceAcc.AddForce(force);
			}
		}
	}
}
