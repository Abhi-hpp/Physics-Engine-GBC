#include "DragForceSystem.h"

namespace Reality
{
	DragForceSystem::DragForceSystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<DragForceComponent>();
		requireComponent<ParticleComponent>();
	}

	void DragForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto& drag = e.getComponent<DragForceComponent>();
			auto& particle = e.getComponent<ParticleComponent>();

			float velocityMag = glm::length(particle.velocity);
			Vector3 force = -glm::normalize(particle.velocity);
			force *= drag.k1 * velocityMag + drag.k2 * pow(velocityMag, 2);

			forceAcc.AddForce(force);



		}
	}
}
