#include "ParticleSphereSystem.h"
#include "ParticleCollideCheck.h"

namespace Reality
{
	ParticleSphereSystem::ParticleSphereSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<ParticleSphereComponent>();
	}

	void ParticleSphereSystem::Update(float deltaTime)
	{
		

		for (int i = 0; i < getEntities().size(); i++)
		{
			auto e = getEntities()[i];
			auto& transform = e.getComponent<TransformComponent>();
			auto& sphere = e.getComponent<ParticleSphereComponent>();

			// Collision with other spheres
			if (i < getEntities().size() - 1)
			{
				for (int j = i + 1; j < getEntities().size(); j++)
				{
					CheckCollision(e, getEntities()[j]);
				}
			}
		}
	}
	void ParticleSphereSystem::CheckCollision(ECSEntity sphereEntityA, ECSEntity sphereEntityB)
	{
		auto& transformA = sphereEntityA.getComponent<TransformComponent>();
		auto& sphereA = sphereEntityA.getComponent<ParticleSphereComponent>();

		auto& transformB = sphereEntityB.getComponent<TransformComponent>();
		auto& sphereB = sphereEntityB.getComponent<ParticleSphereComponent>();

		Vector3 relativePos = transformA.position - transformB.position;
		float distance = glm::length(relativePos);

		if (distance < sphereA.radius + sphereB.radius)
		{
			Vector3 normal = glm::normalize(relativePos);
			float penetration = sphereA.radius + sphereB.radius - distance;

			getWorld().getEventManager().emitEvent<ParticleCollideCheck>(sphereEntityA,	sphereEntityB, 0.8f, normal, penetration );

			getWorld().data.renderUtil->DrawLine(transformA.position - normal * sphereA.radius,	transformB.position + normal * sphereB.radius, Color::Red );
		}
	}
}
