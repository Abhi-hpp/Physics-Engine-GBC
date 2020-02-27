#include "ParticleSphereSystem.h"
#include "ParticleContactEvent.h"
#include "PlaneComponent.h"

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

		for (ECSEntity e : getEntities())
		{
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
				//getWorld().data.renderUtil->DrawSphere(
				//	transform.position,
				//	sphere.radius,
				//	Color::Orange
				//);
			}

			// Collision Check with X
			if (abs(transform.position.x) + sphere.radius >= 50)
			{
				Vector3 normal = Vector3(transform.position.x > 0 ? -1 : 1, 0, 0);
				float penetration = abs(transform.position.x) + sphere.radius - 50;

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
			if (abs(transform.position.y) + sphere.radius >= 50)
			{
				Vector3 normal = Vector3(0, transform.position.y > 0 ? -1 : 1, 0);
				float penetration = abs(transform.position.y) + sphere.radius - 50;

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
			if (abs(transform.position.z) + sphere.radius >= 50)
			{
				Vector3 normal = Vector3(0, 0, transform.position.z > 0 ? -1 : 1);
				float penetration = abs(transform.position.z) + sphere.radius - 50;

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

			for (ECSEntity e2 : getEntities())
			{
				if (!e.hasComponent<PlaneComponent>() && e2.hasComponent<PlaneComponent>())
				{
					CheckCollisionWithPlane(e, e2);
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

	bool ParticleSphereSystem::IsInsidePlane1(Vector3 position, PlaneComponent plane)
	{
		Vector3 v1 = plane.e2.getComponent<TransformComponent>().position - plane.e1.getComponent<TransformComponent>().position;
		Vector3 v2 = plane.e3.getComponent<TransformComponent>().position - plane.e1.getComponent<TransformComponent>().position;
		Vector3 normal = glm::cross(v1, v2);
		Vector3 dis = position - plane.e1.getComponent<TransformComponent>().position;
		float y = glm::dot(glm::cross(v1, dis), normal) / glm::dot(normal, normal);
		float b = glm::dot(glm::cross(dis, v2), normal) / glm::dot(normal, normal);
		float a = 1 - y - b;
		if (((0 <= a) && (a <= 1) && (0 <= b) && (b <= 1) && (0 <= y) && (y <= 1)) )
		{
			return true;
		}
		return false;
	}

	bool ParticleSphereSystem::IsInsidePlane2(Vector3 position, PlaneComponent plane)
	{
		Vector3 v1 = plane.e3.getComponent<TransformComponent>().position - plane.e1.getComponent<TransformComponent>().position;
		Vector3 v2 = plane.e4.getComponent<TransformComponent>().position - plane.e1.getComponent<TransformComponent>().position;
		Vector3 normal = glm::cross(v1, v2);
		Vector3 dis = position - plane.e1.getComponent<TransformComponent>().position;
		float y = glm::dot(glm::cross(v1, dis), normal) / glm::dot(normal, normal);
		float b = glm::dot(glm::cross(dis, v2), normal) / glm::dot(normal, normal);
		float a = 1 - y - b;
		if (((0 <= a) && (a <= 1) && (0 <= b) && (b <= 1) && (0 <= y) && (y <= 1)))
		{
			return true;
		}
		return false;
	}

	void ParticleSphereSystem::CheckCollisionWithPlane(ECSEntity sphereEntityA, ECSEntity planeEntity)
	{
		auto& transform = sphereEntityA.getComponent<TransformComponent>();
		auto& sphere = sphereEntityA.getComponent<ParticleSphereComponent>();
		auto& plane = planeEntity.getComponent<PlaneComponent>();
		
		float distance1 = glm::abs(glm::dot((transform.position - plane.Center1), plane.normal1));
		float distance2 = glm::abs(glm::dot((transform.position - plane.Center2), plane.normal2));

			if (distance1 < sphere.radius && IsInsidePlane1(transform.position, plane))
			{
				plane.bIsColliding1 = true;
				float penetration = sphere.radius - distance1;
				float mult = distance1 > 0 ? -1 : 1;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					sphereEntityA,
					plane.e1,
					0.8f,
					plane.normal1 * -mult,
					penetration
					);
				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					sphereEntityA,
					plane.e2,
					0.8f,
					plane.normal1 * -mult,
					penetration
					);
				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					sphereEntityA,
					plane.e3,
					0.8f,
					plane.normal1 * -mult,
					penetration
					);
			}
			else
			{
				plane.bIsColliding1 = false;
			}
		

		if (distance2 < sphere.radius && IsInsidePlane2(transform.position, plane))
		{
			plane.bIsColliding2 = true;
			float penetration = sphere.radius - distance2;
			float mult = distance2 > 0 ? -1 : 1;
			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				sphereEntityA,
				plane.e1,
				0.8f,
				plane.normal2 * -mult,
				penetration
				);
			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				sphereEntityA,
				plane.e3,
				0.8f,
				plane.normal2 * -mult,
				penetration
				);
			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				sphereEntityA,
				plane.e4,
				0.8f,
				plane.normal2 * -mult,
				penetration
				);
		}
		else
		{
			plane.bIsColliding2 = false;
		}
	}
}
