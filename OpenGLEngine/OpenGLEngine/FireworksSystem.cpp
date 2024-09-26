#include "FireworksSystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"

namespace Reality
{
	FireworksSystem::FireworksSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<FireworksComponent>();
	}

	void FireworksSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& fireworks = e.getComponent<FireworksComponent>();

			fireworks.timer += deltaTime;

			if (fireworks.timer >= fireworks.spawnTime)
			{
				if (fireworks.generation > 0)
				{
					float deltaAngle = 2 * AI_MATH_PI / fireworks.numberOfParticles;

					for (int i = 0; i < fireworks.numberOfParticles; i++)
					{
						auto particle = getWorld().createEntity();
						particle.addComponent<TransformComponent>(transform.position);

						Vector3 velocity = Vector3(0, fireworks.velocityScale, 0);
						float angle = i * deltaAngle;
						velocity.x = cos(angle) * fireworks.velocityScale;
						velocity.z = sin(angle) * fireworks.velocityScale;

						particle.addComponent<ParticleComponent>(velocity);
						particle.addComponent<ForceAccumulatorComponent>();
						particle.addComponent<GravityForceComponent>(0.1f);

						particle.addComponent<FireworksComponent>(
							fireworks.numberOfParticles,
							fireworks.generation - 1,
							fireworks.spawnTime + RANDOM_FLOAT(-0.2f, 0.2f),
							fireworks.velocityScale
							);
					}
				}

				e.kill();
			}
		}
	}
}
