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
			if (fireworks.timer > fireworks.spawnTime)
			{
				if (fireworks.generation > 0)
				{
					float deltaAngle = 2 * AI_MATH_PI / fireworks.numberOfParticles;
					for (int i = 0; i < fireworks.numberOfParticles; i++)
					{
						auto particle = getWorld().createEntity();
						particle.addComponent<TransformComponent>(transform.position);
						float angle = i * deltaAngle;
						Vector3 velocity = Vector3(0, 1, 0);
						velocity.x = cos(angle);
						velocity.z = sin(angle);
						velocity *= fireworks.velocityScale;
						particle.addComponent<ParticleComponent>(velocity);
						particle.addComponent<ForceAccumulatorComponent>();
						particle.addComponent<GravityForceComponent>();
						float colorAlpha = (float)i / (float)fireworks.numberOfParticles;
						particle.addComponent<FireworksComponent>(
							fireworks.numberOfParticles,
							fireworks.generation - 1,
							fireworks.spawnTime + RANDOM_FLOAT(-0.3f, 0.3f),
							fireworks.velocityScale,
							Color(colorAlpha, 0, 1 - colorAlpha)
							);

					}
				}
				e.kill();
			}


			if (DEBUG_LOG_LEVEL > 0)
			{
				getWorld().data.renderUtil->DrawSphere(transform.position, 1.0f, fireworks.color);
			}
		}
	}
}
