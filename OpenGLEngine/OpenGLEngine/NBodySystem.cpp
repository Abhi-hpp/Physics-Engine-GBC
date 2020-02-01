#include "NBodySystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<NBodyComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& nbody = e.getComponent<NBodyComponent>();

			nbody.timer += deltaTime;
			if (nbody.timer > nbody.spawnTime)
			{
				if (nbody.generation > 0)
				{
					for (int i = 0; i < nbody.numberOfParticles; i++)
					{
						auto particle = getWorld().createEntity();
						//transform.position.x = RANDOM_FLOAT(0.0f, 50.0f);
						transform.position.x = 0;
						transform.position.y = 25;
						transform.position.z = -100;
						//transform.position.z = RANDOM_FLOAT(-50.0f, -100.0f);
						particle.addComponent<TransformComponent>(transform.position);

						Vector3 velocity = Vector3(0, 1, 0);
						velocity.x = RANDOM_FLOAT(-50.0f, 50.0f);
						velocity.y = RANDOM_FLOAT(-50.0f, 50.0f);
						velocity.z = RANDOM_FLOAT(-50.0f, 50.0f);
						velocity *= nbody.velocityScale;
						particle.addComponent<ParticleComponent>(velocity);
						particle.addComponent<ForceAccumulatorComponent>();
						particle.addComponent<GravityForceComponent>();
						particle.addComponent<NBodyComponent>(
							nbody.numberOfParticles,
							nbody.generation - 1,
							nbody.spawnTime + RANDOM_FLOAT(-0.3f, 0.3f),
							nbody.lifeSpan,
							nbody.velocityScale
							);
					}
				}
				e.kill();
			}

			if (DEBUG_LOG_LEVEL > 0)
			{
				getWorld().data.renderUtil->DrawSphere(transform.position, 1.0f);
			}
		}
	}
}
