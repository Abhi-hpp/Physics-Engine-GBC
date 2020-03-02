#include "FPSControlSystem.h"
#include "MouseMoveEvent.h"

namespace Reality
{
	FPSControlSystem::FPSControlSystem()
	{
		requireComponent<FPSControlComponent>();
	}


	void FPSControlSystem::Update(float deltaTime)
	{
		GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;
		Camera& camera = getWorld().data.renderUtil->camera;

		// Move
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		for (auto e : getEntities())
		{
			auto &fpsControl = e.getComponent<FPSControlComponent>();

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				camera.ProcessKeyboard(FORWARD, fpsControl.forwardSpeed * deltaTime);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				camera.ProcessKeyboard(BACKWARD, fpsControl.forwardSpeed  * deltaTime);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				camera.ProcessKeyboard(LEFT, fpsControl.sidewaysSpeed * deltaTime);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				camera.ProcessKeyboard(RIGHT, fpsControl.sidewaysSpeed * deltaTime);

			// Look
			auto mouseMoveEvents = getWorld().getEventManager().getEvents<MouseMoveEvent>();
			for (auto event : mouseMoveEvents)
			{
				camera.ProcessMouseMovement(event.deltaX, event.deltaY);
			}
		}
	}
}
