#include "TriangleSystem.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "ParticleSphereComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	TriangleSystem::TriangleSystem()
	{
		requireComponent<TriangleComponent>();
	}

	void TriangleSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& triangle = e.getComponent<TriangleComponent>();

			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;

			if (triangle.entityA.hasComponent<TransformComponent>() &&
				triangle.entityB.hasComponent<TransformComponent>() &&
				triangle.entityC.hasComponent<TransformComponent>() &&
				triangle.sphere.hasComponent<TransformComponent>())
			{
				auto& transformA = triangle.entityA.getComponent<TransformComponent>();
				auto& transformB = triangle.entityB.getComponent<TransformComponent>();
				auto& transformC = triangle.entityC.getComponent<TransformComponent>();

				auto& transformSphere = triangle.sphere.getComponent<TransformComponent>();
				auto& particleSphere = triangle.sphere.getComponent<ParticleComponent>();
				auto& forceAccSphere = triangle.sphere.getComponent<ForceAccumulatorComponent>();

				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
				{
					transformSphere.position = Vector3(RANDOM_FLOAT(-18, 18), RANDOM_FLOAT(30, 35), RANDOM_FLOAT(-8, 8));
					transformSphere.eulerAngles = Vector3(0.0f, 0.0f, 0.0f);
					particleSphere.velocity = Vector3(0.0f, RANDOM_FLOAT(-20, -5), 0.0f);
					particleSphere.acceleration = Vector3(0.0f, 0.0f, 0.0f);
					forceAccSphere.ResetAccumulator();
				}

				auto& sphere = triangle.sphere.getComponent<ParticleSphereComponent>();

				if (DEBUG_LOG_LEVEL > 0)
				{
					getWorld().data.renderUtil->DrawTriangle(transformA.position, transformB.position, transformC.position, Color::Blue);
				}

				Vector3 v1 = transformB.position - transformA.position;
				Vector3 v2 = transformC.position - transformA.position;
				Vector3 cross = glm::cross(v1, v2);
				Vector3 normal = glm::normalize(cross);

				// Find D in the equation: Ax + By + Cz + D = 0, D = - (A * x0) - (B * y0) - (C * z0)
				float dFactor = -normal.x * transformA.position.x - normal.y * transformA.position.y - normal.z * transformA.position.z;

				// Value of A*xs + B*ys + C*zs + D
				float exp1 = normal.x * transformSphere.position.x + normal.y * transformSphere.position.y + normal.z * transformSphere.position.z + dFactor;

				// Value of A^2 + B^2 + C^2
				float exp2 = pow(normal.x, 2.0f) + pow(normal.y, 2.0f) + pow(normal.z, 2.0f);

				// Find the center of the circle formed by the intersection of the sphere with the plane
				float centerX = transformSphere.position.x - ((normal.x * exp1) / exp2);
				
				float centerY = transformSphere.position.y - ((normal.y * exp1) / exp2);
				
				float centerZ = transformSphere.position.z - ((normal.z * exp1) / exp2);

				Vector3 circleCenter = Vector3(centerX, centerY, centerZ);

				float distance = (abs(exp1)) / (sqrt(exp2));

				if (distance < sphere.radius && PointInTriangle(circleCenter, transformA.position, transformB.position, transformC.position))
				{
					float penetration = sphere.radius - distance;
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(
						e,
						triangle.sphere,
						0.2f,
						normal,
						penetration);
				}

			}
		}
	}

	bool TriangleSystem::SameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b)
	{
		Vector3 cp1 = glm::cross(b - a, p1 - a);
		Vector3 cp2 = glm::cross(b - a, p2 - a);
		if (glm::dot(cp1, cp2) >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool TriangleSystem::PointInTriangle(Vector3 p, Vector3 a, Vector3 b, Vector3 c)
	{
		if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
