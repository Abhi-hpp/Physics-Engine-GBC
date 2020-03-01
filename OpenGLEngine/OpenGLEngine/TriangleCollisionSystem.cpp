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
						Vector3 normal = glm::normalize(NomalQuad);

						auto center = i.getComponent<TransformComponent>().position;

						Vector3 someThing = center - pointA;

						float distance = abs(glm::dot(normal, someThing));

						if ((distance < i.getComponent<ParticleSphereComponent>().radius))
						{
							float angleSum = 0;

							Vector3 vPointA = pointA - center;
							Vector3 vPointB = pointB - center;
							Vector3 vPointC = pointC - center;

							float angleA = acos(glm::dot(vPointA, vPointB) / (glm::length(vPointA) * glm::length(vPointB)));
							float angleB = acos(glm::dot(vPointB, vPointC) / (glm::length(vPointB) * glm::length(vPointC)));
							float angleC = acos(glm::dot(vPointA, vPointC) / (glm::length(vPointC) * glm::length(vPointA)));

							angleSum = angleA + angleB + angleC;
							angleSum = angleSum / 3.14f * 180;

							if (angleSum > 350 && angleSum < 370)
							{
								getWorld().getEventManager().emitEvent<ParticleContactEvent>(e, i, 0.8f, normal, i.getComponent<ParticleSphereComponent>().radius - distance);
								getWorld().data.renderUtil->DrawTriangle(pointA, pointB, pointC, Color::Red);
							}
						}
					}
				}
			}
		}
	}
}
