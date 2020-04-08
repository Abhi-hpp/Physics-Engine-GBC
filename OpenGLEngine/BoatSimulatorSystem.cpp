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
		timer += deltaTime;
		for (auto e : getEntities())
		{
			auto& rigidbody = e.getComponent<RigidBodyComponent>();
			auto& eTransform = e.getComponent<TransformComponentV2>();
			auto& boat = e.getComponent<BoatSimulatorComponent>();




			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				rigidbody.AddForce(eTransform.LocalToWorldDirection(boat.propulsion+Vector3(0, i * 15, 0)));
				if (i > -15)
				{
					eTransform.SetRotX(false);
					i -= 0.5;
				}
			}

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
			{
				if (i < 0)
				{
					eTransform.SetRotX(true);
					i += 0.5;
				}
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				rigidbody.AddForce(eTransform.LocalToWorldDirection(-(boat.propulsion + Vector3(0, i * 15, 0))));
				if (i < 15)
				{
					eTransform.SetRotX(true);
					i += 0.5;
				}
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
			{
				if (i > 0)
				{
					eTransform.SetRotX(false);
					i -= 0.5;
				}
			}

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				eTransform.SetRotZ(true);
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				eTransform.SetRotZ(false);
			}
		}



		if (getEntities().size() > 0)
		{
			float width = getWorld().data.renderUtil->window->width;
			float height = getWorld().data.renderUtil->window->height;

			// getWorld().data.renderUtil->RenderText("W , S - Pitch Controls", width / 2 - 100.0f, 60.0f, 0.4f, Color::Orange);
			// getWorld().data.renderUtil->RenderText("A , D - Yaw   Controls", width / 2 - 100.0f, 35.0f, 0.4f, Color::Orange);
			// getWorld().data.renderUtil->RenderText("Q , E - Roll   Controls", width / 2 - 100.0f, 10.0f, 0.4f, Color::Orange);
		}

	}
}
