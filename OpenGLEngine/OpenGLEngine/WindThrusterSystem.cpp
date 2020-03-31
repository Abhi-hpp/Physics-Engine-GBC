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

			if (wind.targetEntity.hasComponent<TransformComponentV2>() &&
				wind.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& transform = wind.targetEntity.getComponent<TransformComponentV2>();
				auto& forceAndTorque = wind.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				Vector3 worldWindDirection = transform.LocalToWorldDirection(wind.localWindDirection);
				forceAndTorque.AddForce(worldWindDirection * wind.wind);

				wind.sailPosition = transform.LocalToWorldPosition(wind.sailPosition);

				wind.timer += deltaTime;
				
				GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				{
					if (wind.wind < 100)
					{
						wind.localWindDirection = Vector3(0, 0, -1);
						wind.wind += 0.01;
					}
				} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				{
					if (wind.wind < 100)
					{
						wind.localWindDirection = Vector3(0, 0, 1);
						wind.wind += 0.01;
					}
				}

				if (wind.timer > 0.3f)
				{
					auto smokeTrail = getWorld().createEntity();
					smokeTrail.addComponent<TransformComponentV2>(Vector3(transform.GetPosition().x, 5.0f, transform.GetPosition().z) - worldWindDirection * 10.0f);
					smokeTrail.addComponent<LifeTimeComponent>();
					wind.timer = 0;
				}
			}
		}
	}
}
