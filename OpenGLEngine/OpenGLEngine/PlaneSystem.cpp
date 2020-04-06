#include "PlaneSystem.h"
#include "ParticleSphereComponent.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"
#include "TriangleComponent.h"

namespace Reality
{
	PlaneSystem::PlaneSystem()
	{
		requireComponent<PlaneComponent>();
	}

	void PlaneSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			for (auto e2 : getEntities())
			{
			}
		}
	}
	void PlaneSystem::CheckCollision(ECSEntity PlaneEntity, ECSEntity sphereEntity)
	{
		Vector3 position = sphereEntity.getComponent<TransformComponent>().position;
		float radius = sphereEntity.getComponent<ParticleSphereComponent>().radius;
		auto& plane = PlaneEntity.getComponent<PlaneComponent>();
		

		float dist1 = glm::abs(glm::dot((position - plane.Triangle1.Center), plane.Triangle1.Normal));
		float dist2 = glm::abs(glm::dot((position - plane.Triangle2.Center), plane.Triangle2.Normal));
		cout << plane.Triangle1.Center.x << endl;
		if (dist1 < radius)
		{
			float Pen = radius - dist1;
			getWorld().getEventManager().emitEvent<ParticleContactEvent>(sphereEntity, PlaneEntity, 0.8f, plane.Triangle1.Normal, Pen);
		}

		if (dist2 < radius)
		{
			float Pen = radius - dist2;

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(sphereEntity, PlaneEntity, 0.8f, plane.Triangle2.Normal, Pen);
		}

	}
}
