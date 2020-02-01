#include "ParticleSystem.h"
#include "ForceAccumulatorComponent.h"

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
				float mass = 1 / e.getComponent<ForceAccumulatorComponent>().inverseMass;
				float r = mass / 10;
				float g = 1 - r;
				getWorld().data.renderUtil->DrawSphere(transform.position, 1, Color(r, g, 0));
			}
		}
	}
}
