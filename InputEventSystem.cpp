#include "InputEventSystem.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MouseMoveEvent.h"

namespace Reality
{
	InputEventSystem::InputEventSystem()
	{
	}

	void InputEventSystem::Update(float deltaTime)
	{
		// Process Mouse
		if (firstMouse)
		{
			glfwGetCursorPos(getWorld().data.renderUtil->window->glfwWindow, &mouseX, &mouseY);
			firstMouse = false;
		}

		double currentMouseX, currentMouseY;
		glfwGetCursorPos(getWorld().data.renderUtil->window->glfwWindow, &currentMouseX, &currentMouseY);
		float deltaX = currentMouseX - mouseX;
		float deltaY = currentMouseY - mouseY;
		getWorld().getEventManager().emitEvent<MouseMoveEvent>(currentMouseX, currentMouseY, deltaX, -deltaY);
		mouseX = currentMouseX;
		mouseY = currentMouseY;
	}
}
