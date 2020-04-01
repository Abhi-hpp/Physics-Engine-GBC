#include "ParticleSystem.h"

namespace Reality
{
	ParticleSystem::ParticleSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<ParticleComponent>();
	}

	void ParticleSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& particle = e.getComponent<ParticleComponent>();

			particle.velocity += particle.acceleration * deltaTime;
			transform.SetPosition(transform.GetPosition() + particle.velocity * deltaTime);

			if (DEBUG_LOG_LEVEL > 0)
			{
				getWorld().data.renderUtil->DrawSphere(transform.GetPosition());
			}
		}
	}
}
