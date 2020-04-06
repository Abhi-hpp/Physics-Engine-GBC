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
			//getWorld().data.renderUtil->DrawCube(
			//	Vector3(0, 0, 0),
			//	Vector3(20, 20, 20),
			//	Vector3(0, 0, 0),
			//	Color::Purple
			//);
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
				//getWorld().data.renderUtil->DrawSphere(
				//	transform.position,
				//	sphere.radius,
				//	Color::Orange
				//);
			}
		}
			
	}
	
}
