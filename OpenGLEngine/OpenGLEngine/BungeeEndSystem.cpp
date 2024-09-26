#include "BungeeEndSystem.h"
#include "SpawnBungeeEvent.h"

namespace Reality
{
	BungeeEndSystem::BungeeEndSystem()
	{
		requireComponent<BungeeEndComponent>();
	}

	void BungeeEndSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungee = e.getComponent<BungeeEndComponent>();

			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				if (!spacePressed && !bungee.connectedTo)
				{
					getWorld().getEventManager().emitEvent<SpawnBungeeEvent>(e);
					bungee.connectedTo = true;

					spacePressed = true;
				}
			}
			else if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
			{
				spacePressed = false;
			}
		}
	}
}
