#include "TrianglePlaneCollisionSystem.h"
#include "ParticleContactEvent.h"
#include "TransformComponent.h"
#include "ParticleSphereComponent.h"

namespace Reality
{
	TrianglePlaneCollisionSystem::TrianglePlaneCollisionSystem()
	{
		//requireComponent<TrianglePlaneComponent>();
	}

	void TrianglePlaneCollisionSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (e.hasComponent<TrianglePlaneComponent>()) // check to have the TrianglePlaneComponent
			{
				auto& plane = e.getComponent<TrianglePlaneComponent>();

				getWorld().data.renderUtil->DrawTriangle(plane.p1.getComponent<TransformComponent>().position, 
					plane.p2.getComponent<TransformComponent>().position, 
					plane.p3.getComponent<TransformComponent>().position, plane.color);

				for (auto s : getEntities())
				{
					if (s.hasComponent<ParticleSphereComponent>())
					{
						auto& sphere = s.getComponent<ParticleSphereComponent>();
						if (s.hasComponent<TransformComponent>())
						{
							auto& transform = s.getComponent<TransformComponent>();
							Vector3 p21 = plane.p1.getComponent<TransformComponent>().position - plane.p2.getComponent<TransformComponent>().position;
							Vector3 p23 = plane.p3.getComponent<TransformComponent>().position - plane.p2.getComponent<TransformComponent>().position;

							//lines for the two sides of the planes
							p21 = glm::normalize(p21);
							p23 = glm::normalize(p23);

							//finds the normal from the plane
							Vector3 Norm = glm::cross(p23, p21); // goes in direction from plane to sphere

							float D = -1 * glm::dot(Norm, plane.p1.getComponent<TransformComponent>().position);
							float d = glm::dot(Norm, transform.position) + D; //actual distance
							

							if (abs(d) < sphere.radius) // colliding
							{
								Vector3 contactPoint = transform.position + (-Norm * d);

								Vector3 p1C = plane.p1.getComponent<TransformComponent>().position - contactPoint;
								Vector3 p2C = plane.p2.getComponent<TransformComponent>().position - contactPoint;
								Vector3 p3C = plane.p3.getComponent<TransformComponent>().position - contactPoint;

								float angle1 = acos(glm::dot(p1C, p2C) / (glm::length(p1C)*glm::length(p2C)));
								angle1 = glm::degrees(angle1);
								float angle2 = acos(glm::dot(p2C, p3C) / (glm::length(p2C)*glm::length(p3C)));
								angle2 = glm::degrees(angle2);
								float angle3 = acos(glm::dot(p3C, p1C) / (glm::length(p3C)*glm::length(p1C)));
								angle3 = glm::degrees(angle3);

								float totalangle = angle1 + angle2 + angle3;

								//if the contact point is within the triangle
								if (totalangle >= 359.8f && totalangle <= 360.2)
								{
									plane.color = Color::Red;
									getWorld().getEventManager().emitEvent<ParticleContactEvent>(
										s,
										e,
										0.8f,
										Norm,
										fabs(sphere.radius - d)
										);
								}
							}
							else
								plane.color = Color::Blue;
						}
					}
				}
			}
		}
	}
}
