#include "TriangleSystem.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
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
			bool contact = false;

			auto& triangle = e.getComponent<TriangleComponent>();

			auto& aPosition = triangle.a.getComponent<TransformComponent>().position;
			auto& bPosition = triangle.b.getComponent<TransformComponent>().position;
			auto& cPosition = triangle.c.getComponent<TransformComponent>().position;


			auto& playerPosition = player.getComponent<TransformComponent>().position;
			auto playerRadius = 1;
			
			Vector3 planeNormal = glm::normalize(glm::cross((cPosition - aPosition), (bPosition - aPosition)));

			Vector3 planeCenter = (aPosition + bPosition + cPosition) / 3.0f;


			float dist = SignedDistanceFromPlane(planeNormal, planeCenter, playerPosition);
			if (abs(dist) < playerRadius && InsideTriangle(triangle, planeNormal, playerPosition))
			{
				float mult = dist > 0 ? -1 : 1;
				getWorld().getEventManager().emitEvent<ParticleContactEvent>(player, triangle.a, 0.8f, -planeNormal * mult, playerRadius - abs(dist));
				getWorld().getEventManager().emitEvent<ParticleContactEvent>(player, triangle.b, 0.8f, -planeNormal * mult, playerRadius - abs(dist));
				getWorld().getEventManager().emitEvent<ParticleContactEvent>(player, triangle.c, 0.8f, -planeNormal * mult, playerRadius - abs(dist));
				
				contact = true;
			}

			if (DEBUG_LOG_LEVEL > 0)
			{
				Color triColor = (contact ? Color(Color::Red) : Color(Color::Purple));
				getWorld().data.renderUtil->DrawTriangle(aPosition, bPosition, cPosition, triColor);
			}
		}

		GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS
			|| player.getComponent<TransformComponent>().position.y <= -100.0f)
		{
			player.getComponent<TransformComponent>().position = Vector3(RANDOM_FLOAT(-17, 23), 10, RANDOM_FLOAT(-5, 5));
			player.getComponent<ParticleComponent>().acceleration = Vector3(0, 0, 0);
			player.getComponent<ParticleComponent>().velocity = Vector3(0, 0, 0);
		}
	}
	float TriangleSystem::SignedDistanceFromPlane(Vector3 planeNormal, Vector3 planeCenter, Vector3 position)
	{
		float d = -((planeNormal.x * planeCenter.x) + (planeNormal.y * planeCenter.y) + (planeNormal.z * planeCenter.z));
		float distance;

		distance = ((planeNormal.x * position.x) + (planeNormal.y * position.y) + (planeNormal.z * position.z) + d) 
			/ (sqrt(planeNormal.x * planeNormal.x + planeNormal.y * planeNormal.y + planeNormal.z * planeNormal.z));

		return distance;
	}
	bool TriangleSystem::InsideTriangle(TriangleComponent tri, Vector3 planeNormal, Vector3 position)
	{
		// first project the player's point on the plane

		Vector3 projPosition = position - (position * planeNormal / planeNormal * planeNormal) * planeNormal;
		// then test the point to see if it's in the triangle

		Vector3 APosition = tri.a.getComponent<TransformComponent>().position;
		Vector3 BPosition = tri.b.getComponent<TransformComponent>().position;
		Vector3 CPosition = tri.c.getComponent<TransformComponent>().position;

		if (SameSide(projPosition, APosition, BPosition, CPosition)
			&& SameSide(projPosition, BPosition, APosition, CPosition)
			&& SameSide(projPosition, CPosition, APosition, BPosition)
			)
		{
			return true;
		}

		else
		{
			return false;
		}
		
	}
	bool TriangleSystem::SameSide(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4)
	{
		Vector3 cp1 = glm::cross(p4 - p3, p1 - p3);
		Vector3 cp2 = glm::cross(p4 - p3, p2 - p3);

		if (glm::dot(cp1, cp2) >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
