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

			//Update Timer
			fireworks.timer += deltaTime;

			//Spawn new particles
			if (fireworks.timer > fireworks.spawnTime)
			{
				if (fireworks.generation > 0)
				{
					float angleRate = 2 * AI_MATH_PI / fireworks.numParticles;
					for (int i = 0; i <= fireworks.numParticles; i++)
					{
						auto particle = getWorld().createEntity();
						particle.addComponent<TransformComponent>(transform.position);
						float angle = i * angleRate;
						Vector3 velocity = Vector3(0, 1, 0);
						velocity.x = cos(angle);
						velocity.y = sin(angle);
						velocity *= fireworks.velocityScale;
						particle.addComponent<ParticleComponent>(velocity);
						particle.addComponent<ForceAccumulatorComponent>();
						particle.addComponent<GravityForceComponent>(0.1f);
						particle.addComponent<FireworksComponent>(
							fireworks.numParticles,
							fireworks.generation - 1,
							fireworks.spawnTime,
							fireworks.velocityScale);
					}
				}
				//Kill old particle
				e.kill();
			}

			if (DEBUG_LOG_LEVEL > 0)
			{
				getWorld().data.renderUtil->DrawSphere(transform.position);
			}
		}
	}
}
