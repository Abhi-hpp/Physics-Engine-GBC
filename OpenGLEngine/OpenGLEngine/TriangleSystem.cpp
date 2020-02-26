#include "TriangleSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"


namespace Reality
{
	TriangleSystem::TriangleSystem()
	{
		requireComponent<TriangleComponent>();
	}

	void TriangleSystem::Update(float deltaTime)
	{
		if (sphere != 0)
		{
			for (auto e : getEntities())
			{
				// For each triangle, draw a debug triangle.

				auto& triangle = e.getComponent<TriangleComponent>();

				Vector3 transformA = triangle.pointA.getComponent<TransformComponent>().position;
				Vector3 transformB = triangle.pointB.getComponent<TransformComponent>().position;
				Vector3 transformC = triangle.pointC.getComponent<TransformComponent>().position;

				// Calculate centre of triangle
				Vector3 centre = (transformA + transformB + transformC) / 3.0f;

				// 1. Calculate two vectors, AB and AC.
				Vector3 AB = transformB - transformA;
				Vector3 AC = transformC - transformA;

				// 2. Determine the normal vector.
				Vector3 normalizedNormal = glm::normalize(glm::cross(AB, AC));
				getWorld().data.renderUtil->DrawLine(centre, centre - (normalizedNormal), Color::Red);

				// Calculating the 'd' component of ax + by + cz = d, or, 'getting that D'
				float planeD = -(normalizedNormal.x * centre.x + normalizedNormal.y * centre.y + normalizedNormal.z * centre.z);

				// Putting d component on end of our normalized normal to create a 4-component vector
				Vector4 plane = Vector4(normalizedNormal, planeD);

				// Sphere position with a 1 on the end, as we are working with Vector4s
				Vector4 spherePos = Vector4(sphere.getComponent<TransformComponent>().position, 1);

				// Calculating distance using the dot product between a vector to the plane and a vector to the centre of the sphere
				float distance = glm::dot(plane, spherePos);
				
				// The normal of the plane (not normalized)
				Vector3 n = glm::cross(AB, AC);

				// Distance from a point on the plane to the position of the particle
				Vector3 w = sphere.getComponent<TransformComponent>().position - transformA;

				// Using barycentric coordinates to calculate angles between sphere and triangle

				// Angle between plane normal and a vector perpendicular to plane and to sphere centre
				float alpha = glm::dot(glm::cross(AB, w), n) / glm::dot(n, n);
				// Angle between plane normal and a (different) vector perpendicular to plane and to sphere centre
				float beta = glm::dot(glm::cross(w, AC), n) / glm::dot(n, n);

				float gamma = 1 - alpha - beta;

				// Point is inside plane if:

				if ((gamma >= 0) && (gamma <= 1) && (beta >= 0) && (beta <= 1) &&(alpha >= 0) && (alpha <= 1))
				{
					if (distance < 1 && distance > -1)
					{
						float penetration = 1 - distance;

						getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.pointA, sphere, 0.8f, normalizedNormal, penetration);
						getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.pointB, sphere, 0.8f, normalizedNormal, penetration);
						getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.pointC, sphere, 0.8f, normalizedNormal, penetration);
						getWorld().data.renderUtil->DrawTriangle(transformA, transformB, transformC, Color::Red);
					}
				}
				else
				{
					getWorld().data.renderUtil->DrawTriangle(transformA, transformB, transformC, Color::Green);
				}

			}
		}

	}

}
