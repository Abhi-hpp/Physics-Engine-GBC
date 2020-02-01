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
		if (!Creatawall)
		{
			wallDummy = getWorld().createEntity();
		}

		
		for (auto e : getEntities())
		{		
			auto& transform = e.getComponent<TransformComponent>();
			auto& sphere = e.getComponent<ParticleSphereComponent>();
			if (DEBUG_LOG_LEVEL > 0)
			{
				
				getWorld().data.renderUtil->DrawCube(transform.position, glm::vec3(20, 20, 20), transform.orientation, Color::Orange);
			}

			if (abs(transform.position.y) + sphere.radius >= 10)
			{
				Vector3 normal = Vector3(0, transform.position.y > 0 ? -1 : 1, 0);
				float penetration = abs(transform.position.y) + sphere.radius - 10;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(e, wallDummy, 1.0f,
					normal,
					penetration);

				//getWorld().data.renderUtil->DrawLine(
				//	transform.position - normal * sphere.radius,
				//	transform.position - normal * (sphere.radius - penetration),
				//	Color::Red);
			}

			if (abs(transform.position.x) + sphere.radius >= 10)
			{
				Vector3 normal = Vector3(0, transform.position.x > 0 ? -1 : 1, 0);
				float penetration = abs(transform.position.x) + sphere.radius - 10;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(e, wallDummy, 1.0f,
					normal,
					penetration);

				//getWorld().data.renderUtil->DrawLine(
				//	transform.position - normal * sphere.radius,
				//	transform.position - normal * (sphere.radius - penetration),
				//	Color::Red);
			}

			if (abs(transform.position.z) + sphere.radius >= 10)
			{
				Vector3 normal = Vector3(0, transform.position.z > 0 ? -1 : 1, 0);
				float penetration = abs(transform.position.z) + sphere.radius - 10;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(e, wallDummy, 1.0f,
					normal,
					penetration);

				//getWorld().data.renderUtil->DrawLine(
				//	transform.position - normal * sphere.radius,
				//	transform.position - normal * (sphere.radius - penetration),
				//	Color::Red);
			}
		}
	}
}
