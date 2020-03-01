#include "TriangleCollisionSystem.h"
#include "ParticleContactEvent.h"
#include "TransformComponent.h"


namespace Reality
{
	TriangleCollisionSystem::TriangleCollisionSystem()
	{

	}

	void TriangleCollisionSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (e.hasComponent<TriangleCollisionComponent>()) // If entity has component collision
			{
				for (auto i : getEntities())
				{
					if (i.hasComponent<ParticleSphereComponent>())
					{
						auto Quad = e.getComponent<TriangleCollisionComponent>();
						Vector3 pointA = Quad.E1.getComponent<TransformComponent>().position;
						Vector3 pointB = Quad.E2.getComponent<TransformComponent>().position;
						Vector3 pointC = Quad.E3.getComponent<TransformComponent>().position;

						Vector3 pointAB = glm::normalize(pointB - pointA);
						Vector3 pointAC = glm::normalize(pointC - pointA);

						Vector3 NomalQuad = glm::cross(pointAB, pointAC);
						Vector3 UnitNorm = glm::normalize(NomalQuad);

						auto center = i.getComponent<TransformComponent>().position;

						Vector3 someThing = center - pointA;

						float distance = abs(glm::dot(UnitNorm, someThing));

						if ((distance < i.getComponent<ParticleSphereComponent>().radius))
						{

							float angleSum = 0;

							Vector3 vA = pointA - center;
							Vector3 vB = pointB - center;
							Vector3 vC = pointC - center;

							float angle1 = acos(glm::dot(vA, vB) / (glm::length(vA) * glm::length(vB)));
							float angle2 = acos(glm::dot(vB, vC) / (glm::length(vB) * glm::length(vC)));
							float angle3 = acos(glm::dot(vA, vC) / (glm::length(vC) * glm::length(vA)));

							angleSum = angle1 + angle2 + angle3;
							angleSum = angleSum / 3.14592654f * 180;

							if (angleSum > 340 && angleSum < 370)
							{
								getWorld().getEventManager().emitEvent<ParticleContactEvent>(e, i, 0.8f, UnitNorm, i.getComponent<ParticleSphereComponent>().radius - distance);
								getWorld().data.renderUtil->DrawTriangle(pointA, pointB, pointC, Color::Red);
							}
						}

					}
				}
			}

		}
	}
}
