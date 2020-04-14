#include "BoatSimulatorSystem.h"
#include "LifeTimeComponent.h"

namespace Reality
{
	BoatSimulatorSystem::BoatSimulatorSystem()
	{
		requireComponent<BoatSimulatorComponent>();
		requireComponent<RigidBodyComponent>();
		requireComponent<TransformComponentV2>();
	}

	void BoatSimulatorSystem::Update(float deltaTime)
	{
		GLFWwindow *window = getWorld().data.renderUtil->window->glfwWindow;


		for (auto e : getEntities())
		{
			auto& rigidBody = e.getComponent<RigidBodyComponent>();
			auto& eTransform = e.getComponent<TransformComponentV2>();
			auto& boat = e.getComponent<BoatSimulatorComponent>();




			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				rigidBody.AddForce(eTransform.LocalToWorldDirection(boat.p +Vector3(0, movement * 5, 0)));
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				rigidBody.AddForce(eTransform.LocalToWorldDirection(-(boat.p + Vector3(0, movement * 5, 0))));
				
			}
		}

		if (getEntities().size() > 0)
		{
			float width = getWorld().data.renderUtil->window->width;
			float height = getWorld().data.renderUtil->window->height;

		}

	}
}
