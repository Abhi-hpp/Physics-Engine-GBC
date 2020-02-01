#include "ParticleSpawnerSystem.h"

namespace Reality
{
	ParticleSpawnerSystem::ParticleSpawnerSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<ParticleSpawnerComponent>();
	}

	void ParticleSpawnerSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& particleSpawner = e.getComponent<ParticleSpawnerComponent>();

			particleSpawner.timer += deltaTime;

			if (particleSpawner.timer >= particleSpawner.spawnTime)
			{
				for (int i = 0; i < particleSpawner.numberOfParticles; i++)
				{
					auto particle = getWorld().createEntity();
					particle.addComponent<TransformComponent>(transform.position);
				}

				particleSpawner.timer = 0;
			}
		}
	}
}
