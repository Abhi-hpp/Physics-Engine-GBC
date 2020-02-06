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
			auto& Nbody = e.getComponent<NBodyComponent>();
		
			if (e.hasComponent<NBodyComponent>())
			{
				for (auto e2 : getEntities())
				{
					auto& ForceAcc2 = e2.getComponent<ForceAccumulatorComponent>();
					auto& Particle2 = e2.getComponent<ParticleSphereComponent>();
					auto& Nbody2 = e2.getComponent<NBodyComponent>();

					if (e2.hasComponent<NBodyComponent>() && e2 != e)
					{
						glm::vec3 Length = e2.getComponent<TransformComponent>().position -
							e.getComponent<TransformComponent>().position;
						float force = 40.0f * (Nbody.mass * Nbody2.mass) / glm::length(Length);
						glm::vec3 dir = glm::normalize(Length);
						ForceAcc.AddForce(force * dir);
					}
				}

			}
		}
	}
}
