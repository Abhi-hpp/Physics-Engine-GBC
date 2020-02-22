#include "TriangleSystem.h"
#include "TransformComponent.h"
#include "ParticleSphereComponent.h"
#include "ParticleContactEvent.h"
#include "ParticleSphereComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"

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

			auto& vertexTransformA = triangle.vertexA.getComponent<TransformComponent>();
			auto& vertexTransformB = triangle.vertexB.getComponent<TransformComponent>();
			auto& vertexTransformC = triangle.vertexC.getComponent<TransformComponent>();

			auto& sphere = triangle.sphere;
			auto& S = sphere.getComponent<TransformComponent>().position;

			// Find the normal
			Vector3 AtoB = glm::vec3(vertexTransformB.position.x - vertexTransformA.position.x,
									 vertexTransformB.position.y - vertexTransformA.position.y,
									 vertexTransformB.position.z - vertexTransformA.position.z);

			Vector3 AtoC = glm::vec3(vertexTransformC.position.x - vertexTransformA.position.x,
									 vertexTransformC.position.y - vertexTransformA.position.y,
									 vertexTransformC.position.z - vertexTransformA.position.z);

			Vector3 planeToPoint = glm::vec3(vertexTransformA.position.x - S.x,
											 vertexTransformA.position.y - S.y,
											 vertexTransformA.position.z - S.z);

			// Calculate the cross product and normal
			Vector3 cross = glm::cross(AtoB, AtoC);
			float crossMagnitude = sqrt(cross.x * cross.x + cross.y * cross.y + cross.z * cross.z);
			Vector3 normal = glm::normalize(cross);

			float D = -(vertexTransformA.position.x * cross.x) + -(vertexTransformA.position.y * cross.y) + -(vertexTransformA.position.z * cross.z);

			// Get the coefficients of a plane
			Vector4 plane = Vector4(cross.x, cross.y, cross.z, D);

			float squareDistance = (plane.x * S.x + plane.y * S.y + plane.z * S.z + plane.w)
				/ (plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);

			float intersectionCircleX = S.x - (plane.x * squareDistance);
			float intersectionCircleY = S.y - (plane.y * squareDistance);
			float intersectionCircleZ = S.z - (plane.z * squareDistance);

			// Distance from point of intersection to sphere center
			float distance = glm::abs(plane.x * S.x + plane.y * S.y + plane.z * S.z + plane.w)
				/ glm::sqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);

			// Amount of intersection based on how much the sphere is penetrating the plane
			float intersectionCircleRadius = glm::sqrt(glm::pow(sphere.getComponent<ParticleSphereComponent>().radius, 2)
				- glm::pow(distance, 2));

			if (sphere.getComponent<ParticleSphereComponent>().radius >= distance &&
				CheckIntersection(vertexTransformA.position, vertexTransformB.position, vertexTransformC.position, Vector3(intersectionCircleX, intersectionCircleY, intersectionCircleZ)))
			{
				float penetration = abs(distance - sphere.getComponent<ParticleSphereComponent>().radius);

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					triangle.sphere,
					e,
					0.8f,
					normal,
					penetration * 0.1
					);
				getWorld().data.renderUtil->DrawTriangle(vertexTransformA.position, vertexTransformB.position, vertexTransformC.position, Color::Red);
			}
			else
			{
				getWorld().data.renderUtil->DrawTriangle(vertexTransformA.position, vertexTransformB.position, vertexTransformC.position, Color::Blue);
			}

			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;
			
			static int oldState = GLFW_RELEASE;
			int newState = glfwGetKey(window, GLFW_KEY_E);

			if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
			{
				sphere.kill();

				auto sphere = getWorld().createEntity();
				sphere.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-20, 20), RANDOM_FLOAT(0, 15), RANDOM_FLOAT(-4, 4)));
				sphere.addComponent<ParticleComponent>();
				sphere.addComponent<ForceAccumulatorComponent>(1.0f);
				sphere.addComponent<GravityForceComponent>();
				sphere.addComponent<ParticleSphereComponent>(1);

				for (auto e : getEntities())
				{
					e.getComponent<TriangleComponent>().sphere = sphere;
				}
			}
			oldState = newState;
		}
	}

	// Figure out if the sum of the area of the triangles formed by intersection point P 
	// equals to the sum of the triangle ABC
	bool TriangleSystem::CheckIntersection(Vector3 A, Vector3 B, Vector3 C, Vector3 P)
	{
		Vector3 AB = Vector3(B.x - A.x, B.y - A.y, B.z - A.z);
		Vector3 AC = Vector3(C.x - A.x, C.y - A.y, C.z - A.z);

		Vector3 PA = Vector3(A.x - P.x, A.y - P.y, A.z - P.z);
		Vector3 PB = Vector3(B.x - P.x, B.y - P.y, B.z - P.z);
		Vector3 PC = Vector3(C.x - P.x, C.y - P.y, C.z - P.z);

		float areaABC = 0.5f * glm::length(glm::cross(AB, AC));
		float areaPAB = 0.5f * glm::length(glm::cross(PA, PB));
		float areaPAC = 0.5f * glm::length(glm::cross(PA, PC));
		float areaPBC = 0.5f * glm::length(glm::cross(PB, PC));

		return (areaABC == areaPAB + areaPAC + areaPBC);

		return false;
	}
}
