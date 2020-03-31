#include "WindThrusterSystem.h"
#include "TransformComponentV2.h"
#include "LifeTimeComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	WindThrusterSystem::WindThrusterSystem()
	{
		requireComponent<WindThrusterComponent>();
	}

	void WindThrusterSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& wind = e.getComponent<WindThrusterComponent>();

			if (wind.attachedEntity.hasComponent<TransformComponentV2>() &&
				wind.attachedEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& transform = wind.attachedEntity.getComponent<TransformComponentV2>();
				auto& forceAndTorque = wind.attachedEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				Vector3 worldWindDirection = transform.LocalToWorldDirection(wind.windDirection);
				forceAndTorque.AddForce(worldWindDirection * wind.wind);

				wind.sailPosition = transform.LocalToWorldPosition(wind.sailPosition);

				wind.timer += deltaTime;
				
				WindThrusterInput(wind);
			}
		}
	}

	void WindThrusterSystem::WindThrusterInput(Reality::WindThrusterComponent& wind)
	{
		GLFWwindow* window = getWorld().data.renderUtil->window->glfwWindow;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			wind.windDirection = Vector3(0, 0, -1);
			wind.wind += 0.05;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			wind.windDirection = Vector3(0, 0, 1);
			wind.wind += 0.05;
		}
	}
}
