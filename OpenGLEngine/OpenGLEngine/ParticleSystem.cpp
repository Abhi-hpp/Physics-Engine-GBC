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

			particle.velocity += Vector3(0, -9.8f, 0) * deltaTime;
			transform.position += particle.velocity * deltaTime;
		}
	}
}
