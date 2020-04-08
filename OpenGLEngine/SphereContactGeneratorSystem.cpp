#include "SphereContactGeneratorSystem.h"
#include "ParticleContactComponent.h"


namespace Reality
{
	SphereContactGeneratorSystem::SphereContactGeneratorSystem()
	{
		requireComponent<SphereComponent>();
		requireComponent<ParticleComponent>();
		requireComponent<TransformComponent>();
	}


	void SphereContactGeneratorSystem::Update(float deltaTime)
	{
		if (!dummyCreated)
		{
			dummy = getWorld().createEntity();
			dummyCreated = true;
		}
		auto entities = getEntities();
		for (int i = 0; i < entities.size(); i++)
		{
			auto& transform1 = entities[i].getComponent<TransformComponent>();
			auto& sphere1 = entities[i].getComponent<SphereComponent>();
			auto& particle1 = entities[i].getComponent<ParticleComponent>();
			bool collided = false;
			// Check collisions with other spheres
			if (entities.size() > 1)
			{
				if (i < entities.size() - 1)
				{
					for (int j = i + 1; j < entities.size(); j++)
					{
						auto& transform2 = entities[j].getComponent<TransformComponent>();
						auto& sphere2 = entities[j].getComponent<SphereComponent>();
						auto& particle2 = entities[j].getComponent<ParticleComponent>();

						if (glm::length(transform1.position - transform2.position)
							< sphere1.radius + sphere2.radius)
						{
							float penetration = sphere1.radius + sphere2.radius - 
								glm::length(transform1.position - transform2.position);
							ECSEntity e = getWorld().createEntity();
							Vector3 normal = glm::normalize(transform1.position - transform2.position);

							getWorld().data.renderUtil->DrawLine(transform1.position - sphere1.radius * normal,
								transform1.position - sphere1.radius * normal + penetration * normal, Color(0, 0, 1));

							e.addComponent<ParticleContactComponent>(entities[i],
								entities[j],
								1.0f,
								normal,
								penetration);
							collided = true;
						}
					}
				}
			}
			// Check collision with Hardcoded walls
			if (abs(transform1.position.x) >= 14)
			{
				float penetration = abs(transform1.position.x) - 14;
				ECSEntity e = getWorld().createEntity();
				Vector3 normal = (transform1.position.x > 0 ? -1.0f : 1.0f) * Vector3(1, 0, 0);
				e.addComponent<ParticleContactComponent>(entities[i],
					dummy,
					1.0f,
					normal,
					penetration);
				collided = true;
			}
			if (abs(transform1.position.y - 20) >= 14)
			{
				float penetration = abs(transform1.position.y - 20) - 14;
				ECSEntity e = getWorld().createEntity();
				Vector3 normal = ((transform1.position.y - 20) > 0 ? -1.0f : 1.0f) * Vector3(0, 1, 0);
				e.addComponent<ParticleContactComponent>(entities[i],
					dummy,
					1.0f,
					normal,
					penetration);
				collided = true;
			}
			if (abs(transform1.position.z) >= 14)
			{
				float penetration = abs(transform1.position.z) - 14;
				ECSEntity e = getWorld().createEntity();
				Vector3 normal = (transform1.position.z > 0 ? -1.0f : 1.0f) * Vector3(0, 0, 1);
				e.addComponent<ParticleContactComponent>(entities[i],
					dummy,
					1.0f,
					normal,
					penetration);
				collided = true;
			}
			Color col = collided ? Color(1, 0, 0, 1) : Color(0, 1, 0, 1);
			getWorld().data.renderUtil->DrawSphere(transform1.position, sphere1.radius, col);
		}
		//getWorld().data.renderUtil->DrawCube(Vector3(0, 20, 0), Vector3(30, 30, 30));
	}
}
