#include "TriangleSystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"
#include "PenetrationDeltaMoveComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	bool TriangleSystem::createPlayer = false;
	ECSEntity TriangleSystem::player = ECSEntity();

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			if (TriangleSystem::getCreatePlayer() == true)
			{
				ECSEntity* test = TriangleSystem::getPlayer();
				test->kill();
				TriangleSystem::setCreatePlayer(false);
			}
		}
	}

	TriangleSystem::TriangleSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<TriangleComponent>();
	}

	void TriangleSystem::makePlayer()
	{
		if (!createPlayer)
		{
			player = getWorld().createEntity();
			createPlayer = true;
			player.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(0, 10), 8, RANDOM_FLOAT(-2, 2)));
			player.addComponent<ParticleComponent>(Vector3(0, 0, 0), 0.9f, Color::Blue);
			player.addComponent<ForceAccumulatorComponent>();
			player.addComponent<GravityForceComponent>(0.25f);
			player.addComponent<PenetrationDeltaMoveComponent>();
		}
	}

	bool TriangleSystem::isInside(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 spherePos)
	{
		float AreaABC = glm::length((glm::cross((p2 - p1), (p3 - p1)))) / 2.f;
		float a = glm::length((glm::cross((p2 - spherePos), (p3 - spherePos)))) / (2.f * AreaABC);
		float b = glm::length((glm::cross((p3 - spherePos), (p1 - spherePos)))) / (2.f * AreaABC);
		float y = 1.f - a - b;

		if ((a >= 0) && (b >= 0) && (y >= 0) && (a + b + y == 1))
		{
			std::cout << "yes\n";
			return true;
		}
		else
		{
			std::cout << "no\n";
			return false;
		}
		std::cout << "hitting nothing\n";
		return false;
	}

	void TriangleSystem::Update(float deltaTime)
	{
		glfwSetKeyCallback(getWorld().data.renderUtil->window->glfwWindow, key_callback);

		makePlayer();

		for (auto e : getEntities())
		{
			e1 = e.getComponent<TriangleComponent>().e1;
			e2 = e.getComponent<TriangleComponent>().e2;
			e3 = e.getComponent<TriangleComponent>().e3;

			e1Pos = e1.getComponent<TransformComponent>().position;
			e2Pos = e2.getComponent<TransformComponent>().position;
			e3Pos = e3.getComponent<TransformComponent>().position;

			pos = player.getComponent<TransformComponent>().position;

			Vector3 AB = e2Pos - e1Pos;
			Vector3 AC = e3Pos - e1Pos;

			avg = (e1Pos + e2Pos + e3Pos) / 3.f;
			cross = glm::cross(AB, AC);

			crossNormalized = glm::normalize(cross);

			d = ((cross.x * e1Pos.x) + (cross.y * e1Pos.y) + (cross.z * e1Pos.z)) * -1;

			plane = Vector4(cross.x, cross.y, cross.z, d);
			planeNormalized = glm::normalize(plane);

			D = (glm::abs((cross.x * pos.x) + (cross.y * pos.y) + (cross.z * pos.z) + d)) / std::sqrt((std::pow(cross.x, 2) + std::pow(cross.y, 2) + std::pow(cross.z, 2)));

			getWorld().data.renderUtil->DrawLine(avg, avg + (crossNormalized), Color::Yellow);
			getWorld().data.renderUtil->DrawSphere(avg, 0.1f, Color::Yellow);
		
			if ((D < player.getComponent<ParticleComponent>().radius))
			{
				getWorld().data.renderUtil->DrawTriangle(e3Pos, e1Pos, e2Pos, Color::Green);
				getWorld().data.renderUtil->RenderText("HIT", 1500.0f, 900.0f, 1.f, Color::Red);

				float penetration = abs((planeNormalized.x + planeNormalized.y + planeNormalized.z) / 3) + player.getComponent<ParticleComponent>().radius * 0.01f;

				getWorld().getEventManager().emitEvent<ParticleContactEvent>(
					player,
					e,
					0.45f,
					crossNormalized,
					penetration);
			}
			else
				getWorld().data.renderUtil->DrawTriangle(e3Pos, e1Pos, e2Pos, Color::Red);
		}

	}

}
