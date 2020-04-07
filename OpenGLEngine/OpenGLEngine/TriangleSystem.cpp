#include "TriangleSystem.h"


namespace Reality
{
	TriangleSystem::TriangleSystem()
	{

	}

	void TriangleSystem::Update(float deltaTime)
	{
		for (auto e1 : getEntities())
		{
			if (e1.hasComponent<TriangleComponent>())
			{
				auto& triangle = e1.getComponent<TriangleComponent>();

				for (auto e2 : getEntities())
				{
					if (e2.hasComponent<ParticleSphereComponent>())
					{
						auto& particle = e2.getComponent<ParticleSphereComponent>();

						if (e2.hasComponent<TransformComponent>())
						{
							auto& transform = e2.getComponent<TransformComponent>();
							Vector3 vertex1 = triangle.vertex_1.getComponent<TransformComponent>().position;
							Vector3 vertex2 = triangle.vertex_2.getComponent<TransformComponent>().position;
							Vector3 vertex3 = triangle.vertex_3.getComponent<TransformComponent>().position;

							// Calculate normal 
							Vector3 v1 = glm::normalize(vertex2 - vertex1);
							Vector3 v2 = glm::normalize(vertex2 - vertex3);
							Vector3 normal = glm::cross(v2, v1);

							float distance = glm::dot(normal, transform.position) - glm::dot(normal, vertex2);


							if (abs(distance) <= particle.radius) // if there is interaction
							{
								float penetration = fabs(particle.radius - distance);

								getWorld().getEventManager().emitEvent<ParticleContactEvent>(
									e2,
									e1,
									0.8f,
									normal,
									penetration
									);
								getWorld().data.renderUtil->DrawTriangle(vertex1, vertex2, vertex3, Color::Yellow);
							}
							else // if not
								getWorld().data.renderUtil->DrawTriangle(vertex1, vertex2, vertex3, Color::Brown);
						}
					}
				}
			}
		}
	}
}
