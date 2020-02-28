#include "NBodySystem.h"
#include "ParticleSphereComponent.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<NBodyComponent>();
		requireComponent<ParticleSphereComponent>();
		requireComponent<TransformComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& ForceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto& Particle = e.getComponent<ParticleSphereComponent>();

			if (e.hasComponent<NBodyComponent>())
			{
				for (auto e2 : getEntities())
				{
					auto& ForceAcc2 = e2.getComponent<ForceAccumulatorComponent>();
					auto& Particle2 = e2.getComponent<ParticleSphereComponent>();
					if (e2.hasComponent<NBodyComponent>() && e2 != e)
					{
						glm::vec3 Length = e2.getComponent<TransformComponent>().position - e.getComponent<TransformComponent>().position;
						float force = 15.0f * (Particle.mass * Particle2.mass) / glm::length(Length);
						glm::vec3 dir = glm::normalize(Length);

						ForceAcc.AddForce(force * dir);
					}
				}

			}
		}
	}
}
