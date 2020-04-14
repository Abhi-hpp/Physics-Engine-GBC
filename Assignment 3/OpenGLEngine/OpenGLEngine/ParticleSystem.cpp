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
			auto &particle = e.getComponent<ParticleComponent>();
			auto &transform = e.getComponent<TransformComponent>();

			// HACK for bounce
			if (transform.position.y <= -10)
			{
				//particle.velocity.y = -particle.velocity.y;
				//e.kill();
			}

			// Update velocity from accelarartion
			particle.velocity += particle.accelaration * deltaTime;

			// Update position from velocity
			transform.position += particle.velocity * deltaTime;
		}
	}
}
