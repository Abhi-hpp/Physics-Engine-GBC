#include "BoatSystem.h"
#include "TransformComponentV2.h"

namespace Reality
{
	BoatSystem::BoatSystem()
	{
		requireComponent<TransformComponentV2>();
	}

	void BoatSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();

			getWorld().data.renderUtil->DrawCube(transform.GetPosition(), transform.GetScale(), transform.GetOrientation(), Color::Red);

			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
			{
				transform.SetPosition(Vector3(transform.GetPosition().x + 1, transform.GetPosition().y, transform.GetPosition().z));
			}
			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
			{
				transform.SetPosition(Vector3(transform.GetPosition().x - 1, transform.GetPosition().y, transform.GetPosition().z));
			}
			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
			{
				transform.SetPosition(Vector3(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z - 1));
			}
			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
			{
				transform.SetPosition(Vector3(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z + 1));
			}
		}
	}
}
