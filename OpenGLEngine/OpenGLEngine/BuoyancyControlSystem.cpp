#include "BuoyancyControlSystem.h"

namespace Reality
{
	BuoyancyControlSystem::BuoyancyControlSystem()
	{

	}

	void BuoyancyControlSystem::Update(float deltaTime)
	{
		float density = getWorld().getSystemManager().getSystem<BuoyancySystem>().liquidDensity;
		getWorld().data.renderUtil->RenderText("Liquid Density : " + std::to_string((int)round(density)), 1710.0f, 990.0f, 0.45f, Color(0, 1, 1, 1));

		// Space Key pressed
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if (!spacePressed)
			{
				getWorld().getEventManager().emitEvent<BuoyancyControlEvent>("Space");

				spacePressed = true;
			}
		}
		else if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
			spacePressed = false;

		// Keypad + key pressed
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		{
			if (!plusPressed)
			{
				getWorld().getEventManager().emitEvent<BuoyancyControlEvent>("Plus");

				plusPressed = true;
			}
		}
		else if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_KP_ADD) == GLFW_RELEASE)
			plusPressed = false;

		// Keypad - key pressed
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		{
			if (!minusPressed)
			{
				getWorld().getEventManager().emitEvent<BuoyancyControlEvent>("Minus");

				minusPressed = true;
			}
		}
		else if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_KP_SUBTRACT) == GLFW_RELEASE)
			minusPressed = false;
	}
}
