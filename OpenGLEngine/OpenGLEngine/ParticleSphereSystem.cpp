#include "ParticleSphereSystem.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	ParticleSphereSystem::ParticleSphereSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<ParticleSphereComponent>();
	}

	void ParticleSphereSystem::Update(float deltaTime)
	{
		if (!createBox)
		{
			boundingBox = getWorld().createEntity();
			createBox = true;
		}

		// Draw Bounding Box
		if (getEntities().size() > 0)
		{
			getWorld().data.renderUtil->DrawCube(
				Vector3(0, 0, 0),
				Vector3(20, 20, 20),
				Vector3(0, 0, 0),
				Color::Purple
			);
		}

		for (int i = 0; i < getEntities().size(); i++)
		{
			auto e = getEntities()[i];
			auto& transform = e.getComponent<TransformComponent>();
			auto& sphere = e.getComponent<ParticleSphereComponent>();

			// Draw Debug Sphere
			if (DEBUG_LOG_LEVEL > 0)
			{
				getWorld().data.renderUtil->DrawSphere(
					transform.position,
					sphere.radius,
					Color::Orange
				);
			}

			// Collision Check with X
			if (abs(transform.position.x) + sphere.radius >= 10)
			{
				Vector3 normal = Vector3(transform.position.x > 0 ? -1 : 1, 0, 0);
				float penetration = abs(transform.position.x) + sphere.radius - 10;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					e,
					boundingBox,
					0.8f,
					normal,
					penetration);

				getWorld().data.renderUtil->DrawLine(
					transform.position - normal * sphere.radius,
					transform.position - normal * (sphere.radius - penetration),
					Color::Red);
			}

			// Collision Check with Y
			if (abs(transform.position.y) + sphere.radius >= 10)
			{
				Vector3 normal = Vector3(0, transform.position.y > 0 ? -1 : 1, 0);
				float penetration = abs(transform.position.y) + sphere.radius - 10;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					e,
					boundingBox,
					0.8f,
					normal,
					penetration);

				getWorld().data.renderUtil->DrawLine(
					transform.position - normal * sphere.radius,
					transform.position - normal * (sphere.radius - penetration),
					Color::Red);
			}

			// Collision Check with Z
			if (abs(transform.position.z) + sphere.radius >= 10)
			{
				Vector3 normal = Vector3(0, 0, transform.position.z > 0 ? -1 : 1);
				float penetration = abs(transform.position.z) + sphere.radius - 10;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					e,
					boundingBox,
					0.8f,
					normal,
					penetration);

				getWorld().data.renderUtil->DrawLine(
					transform.position - normal * sphere.radius,
					transform.position - normal * (sphere.radius - penetration),
					Color::Red);
			}

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

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				sphereEntityA,
				sphereEntityB,
				0.8f,
				normal,
				penetration
				);

			getWorld().data.renderUtil->DrawLine(
				transformA.position - normal * sphereA.radius,
				transformB.position + normal * sphereB.radius,
				Color::Red
			);
		}
	}
}
