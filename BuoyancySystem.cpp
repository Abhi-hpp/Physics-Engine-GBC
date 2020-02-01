#include "BuoyancySystem.h"
#include "GravityForceComponent.h"

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
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
		{
			density++;
		}

		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			density--;
		}
		if (density < 0)
		{
			getWorld().data.renderUtil->DrawCube(glm::vec3(-20, -35, 0), glm::vec3(80, 50, 50), glm::vec3(0, 0, 0), Color::Red);
		}
		else
		{
			getWorld().data.renderUtil->DrawCube(glm::vec3(-20, -35, 0), glm::vec3(80, 50, 50), glm::vec3(0, 0, 0), Color::Cyan);
		}
		for (auto e : getEntities())
		{
			auto& objectTrans = e.getComponent<TransformComponent>();
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			float depth = objectTrans.position.y;


			if (depth >= buoyancy.waterHeight + buoyancy.maxDepth)
			{
				e.getComponent<GravityForceComponent>().gravityScale = 1;
				return;
			}


			glm::vec3 force(0, 0, 0);

			if (depth <= buoyancy.waterHeight - buoyancy.maxDepth)
			{
				e.getComponent<GravityForceComponent>().gravityScale = 0;
				force.y = density * buoyancy.volume;
				forceAcc.AddForce(force);
			}
			else
			{
				force.y = (density * buoyancy.volume * (depth - buoyancy.maxDepth - buoyancy.waterHeight) / 2 * buoyancy.maxDepth);
				forceAcc.AddForce(force);
			}


		}
	}
}
