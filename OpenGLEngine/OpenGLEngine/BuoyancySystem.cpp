#include "BuoyancySystem.h"


namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BuoyancyComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		
			getWorld().data.renderUtil->DrawCube(glm::vec3(-20, -35, 0), glm::vec3(80, 50, 50), glm::vec3(0, 0, 0), Color::Cyan);
		
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& ForceAcc = e.getComponent<ForceAccumulatorComponent>();
			float depth = transform.position.y;

			if (depth >= buoyancy.waterHeight + buoyancy.maxDepth)
			{
				e.getComponent<GravityForceComponent>().gravityScale = 1;
				return;
			}

			getWorld().data.renderUtil->DrawCube(glm::vec3(-25, -45, 0), glm::vec3(60, 40, 40), glm::vec3(0, 0, 0), Color::Cyan);
			glm::vec3 force(0, 0, 0);

			if (depth <= buoyancy.waterHeight - buoyancy.maxDepth)
			{
				e.getComponent<GravityForceComponent>().gravityScale = 0;
				force.y = waterDensity * buoyancy.volume;
				ForceAcc.AddForce(force);
			}
			else
			{
				force.y = (waterDensity * buoyancy.volume * (depth - buoyancy.maxDepth - buoyancy.waterHeight) 
					/ 2 * buoyancy.maxDepth);

				ForceAcc.AddForce(force);
			}

		}

		//control density
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			waterDensity--;
		}

		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
		{
			waterDensity++;
		}
	}
}
