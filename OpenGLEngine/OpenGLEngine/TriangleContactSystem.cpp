#include "TriangleContactSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"
#include "ParticleSphereComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"
#include "PenetrationDeltaMoveComponent.h"

namespace Reality
{
	TriangleContactSystem::TriangleContactSystem()
	{
		requireComponent<TriangleComponent>();
	}

	void TriangleContactSystem::Update(float deltaTime)
	{
		//TriangleContactSystem::CreateSphere(sphere);
		
		if (sphereCreated == false)
		{
			sphere = getWorld().createEntity();
			sphere.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-35, 0), 8, -0.0));
			sphere.addComponent<ParticleComponent>();
			sphere.addComponent<ForceAccumulatorComponent>(1.0f);
			sphere.addComponent<GravityForceComponent>();
			sphere.addComponent<PenetrationDeltaMoveComponent>();
			getWorld().getSystemManager().getSystem<TriangleContactSystem>().CreateSphere(sphere);

			sphereCreated = true;
		}

		if (sphereCreated == true)
		{
			for (auto e : getEntities())
			{
				auto& triangle = e.getComponent<TriangleComponent>();
				//auto& sphere = e.getComponent<ParticleSphereComponent>();

				auto& point1 = triangle.p1.getComponent<TransformComponent>().position;
				auto& point2 = triangle.p2.getComponent<TransformComponent>().position;
				auto& point3 = triangle.p3.getComponent<TransformComponent>().position;

				Vector3 triangleCenter = (point1 + point2 + point3) / 3.0f;

				Vector3 v1 = point2 - point1;
				Vector3 v2 = point3 - point1;
				Vector3 planeNormal = glm::normalize(glm::cross(v1, v2));
				float planeD = -(planeNormal.x * triangleCenter.x + planeNormal.y * triangleCenter.y + planeNormal.z * triangleCenter.z);
				Vector4 plane = Vector4(planeNormal, planeD);

				Vector4 spherePos = Vector4(sphere.getComponent<TransformComponent>().position, 1);
				float distance = glm::dot(plane, spherePos); // Position of sphere within plane
				Vector3 dir = Vector3(spherePos) - triangleCenter;
				dir = glm::normalize(dir);

				getWorld().data.renderUtil->DrawTriangle(point1, point2, point3, Color::Blue);

				// u = P2 - P1
				Vector3 u = point2 - point1;
				// v = P3 - P1
				Vector3 v = point3 - point1;
				// n = u x v
				Vector3 n = glm::cross(u, v);
				// w = sphere position - P1
				Vector3 w = sphere.getComponent<TransformComponent>().position - point1;

				// Determine if point is within triangle
				// gamma = [(u x w) dot n] / n^2
				float gamma = glm::dot(glm::cross(u, w), n) / glm::dot(n, n);
				// beta = [(w x v) dot n] / n^2
				float beta = glm::dot(glm::cross(w, v), n) / glm::dot(n, n);
				float alpha = 1 - gamma - beta;

				// The sphere position is inside triangle if:
				// 0 <= alpha <= 1,
				// 0 <= beta <= 1, and
				// 0 <= gamma <= 1.
				if (((0 <= alpha) && (alpha <= 1) && (0 <= beta) && (beta <= 1) && (0 <= gamma) && (gamma <= 1)))
				{
					if (abs(distance) < 1)
					{
						float penetration = 1 - distance;

						getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.p1, sphere, 1.0f, -planeNormal, penetration);
						getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.p2, sphere, 1.0f, -planeNormal, penetration);
						getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.p3, sphere, 1.0f, -planeNormal, penetration);

						//getWorld().data.renderUtil->DrawTriangle(triangle.p1.getComponent<TransformComponent>().position,
						//	triangle.p2.getComponent<TransformComponent>().position,
						//	triangle.p3.getComponent<TransformComponent>().position, Color::Red);
					}
				}
			}
		}
	}
}