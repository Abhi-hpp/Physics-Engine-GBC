#include "ParticleSystem.h"

namespace Reality
{
	ParticleSystem::ParticleSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<ParticleComponent>();
	}

	void ParticleSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& particle = e.getComponent<ParticleComponent>();

			particle.velocity += particle.acceleration * deltaTime;
			transform.position += particle.velocity * deltaTime;

			if (DEBUG_LOG_LEVEL > 0)
			{
				getWorld().data.renderUtil->DrawSphere(transform.position);
			}
		}
	}
}
