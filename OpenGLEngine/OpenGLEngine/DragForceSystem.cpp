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

			float velocityMagn = glm::length(particle.velocity);
			if (velocityMagn > 0)
			{
				Vector3 force = -glm::normalize(particle.velocity);
				force *= drag.k1 * velocityMagn + drag.k2 * pow(velocityMagn, 2);

				forceAcc.AddForce(force);
			}
			
		}
	}
}
