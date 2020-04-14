#include "ParticleSpawnerSystem.h"
#include "ParticleComponent.h"
#include "MeshComponent.h"

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
			auto &particleSpawner = e.getComponent<ParticleSpawnerComponent>();
			auto &transform = e.getComponent<TransformComponent>();

			// Update Timer
			particleSpawner.timer += deltaTime;

			if (particleSpawner.timer >= particleSpawner.duration)
			{
				float deltaAngle = 2 * 3.14f / particleSpawner.numberOfParticles;
				for (int i = 0; i < particleSpawner.numberOfParticles; i++)
				{
					auto e = getWorld().createEntity();
					e.addComponent<TransformComponent>(transform.position, Vector3(0.1f, 0.1f, 0.1f));

					// Calculate velocity, spread out in a circle
					Vector3 velocity;
					velocity.y = particleSpawner.particleSpeed;
					float angle = i * deltaAngle;
					velocity.x = cos(angle) * particleSpawner.particleSpeed;
					velocity.z = sin(angle) * particleSpawner.particleSpeed;

					// Add particle with gravity
					e.addComponent<ParticleComponent>(1.0f, velocity);

					// Add mesh
					e.addComponent<ModelComponent>("Resources/Models/nanosuit/nanosuit.obj");
				}

				// Reset timer
				particleSpawner.timer = 0;
			}
		}
	}
}
