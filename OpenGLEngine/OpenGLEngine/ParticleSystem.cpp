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

			if (1 > 0)
			{
				getWorld().data.renderUtil->DrawSphere(transform.position, 5.0f, Color(1.0f,1.0f,1.0f,1.0f));
				getWorld().data.renderUtil->DrawSphere(transform.position, 5.0f, Color::Red);
			}
		}
	}
}
