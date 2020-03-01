#include "PlaneSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"
#include "ParticleSphereComponent.h"
namespace Reality
{
	PlaneSystem::PlaneSystem()
	{

	}

	void PlaneSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (e.hasComponent<PlaneComponent>())
			{
				auto& plane = e.getComponent<PlaneComponent>(); 

				getWorld().data.renderUtil->DrawTriangle(plane.point1.getComponent<TransformComponent>().position,
					plane.point2.getComponent<TransformComponent>().position, plane.point3.getComponent<TransformComponent>().position, Color::Cyan);

				for (auto sph : getEntities())
				{
					if (sph.hasComponent<ParticleSphereComponent>())
					{
						auto& pSphere = sph.getComponent<ParticleSphereComponent>();
						if (sph.hasComponent<TransformComponent>())
						{
							auto& transform = sph.getComponent<TransformComponent>();

							Vector3 P3P1 = plane.point1.getComponent<TransformComponent>().position - plane.point3.getComponent<TransformComponent>().position;
							Vector3 P3P2 = plane.point2.getComponent<TransformComponent>().position - plane.point3.getComponent<TransformComponent>().position;

							Vector3 normal = glm::cross(P3P1, P3P2);
							normal = glm::normalize(normal);

							float c = -1 * glm::dot(plane.point1.getComponent<TransformComponent>().position, normal);

							float dist = glm::dot(normal, transform.position) + c;

							if (dist <= pSphere.radius)
							{
								Vector3 contactPoint = transform.position + (-normal * dist);

								Vector3 PCP1 = plane.point1.getComponent<TransformComponent>().position - contactPoint;

								Vector3 PCP2 = plane.point2.getComponent<TransformComponent>().position - contactPoint;

								Vector3 PCP3 = plane.point3.getComponent<TransformComponent>().position - contactPoint;
							
								float total = 0;
								total += glm::degrees(acos(glm::dot(PCP1, PCP2) / (glm::length(PCP1) * glm::length(PCP2))));
								total += glm::degrees(acos(glm::dot(PCP2, PCP3) / (glm::length(PCP2) * glm::length(PCP3))));
								total += glm::degrees(acos(glm::dot(PCP3, PCP1) / (glm::length(PCP3) * glm::length(PCP1))));


								if (total == 360)
								{
									getWorld().getEventManager().emitEvent<ParticleContactEvent>(
									sph,
									e,
									0.8f,
									normal,
									fabs(dist - pSphere.radius)
									);


									getWorld().data.renderUtil->DrawTriangle(plane.point1.getComponent<TransformComponent>().position,
										plane.point2.getComponent<TransformComponent>().position, plane.point3.getComponent<TransformComponent>().position, Color::Red);
								}

								
							}
						}
					}
				}

			}
		}
	}
}
