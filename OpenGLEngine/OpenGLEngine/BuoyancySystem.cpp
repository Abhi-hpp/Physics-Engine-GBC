#include "BuoyancySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BuoyancyComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		if (!createBox)
		{
			boundingBox = getWorld().createEntity();
			createBox = true;
		}

		// Draw Bounding Box
		getWorld().data.renderUtil->DrawCube(
			Vector3(0, -15, 0),
			Vector3(30, 30, 30),
			Vector3(0, 0, 0),
			Color::Purple
		);

		for (auto e : getEntities())
		{
			auto& buoyancyTransform = e.getComponent<TransformComponent>();
			auto& buoyancy = e.getComponent<BuoyancyComponent>();

			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;

			if (buoyancy.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& buoyancy.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forceAcc = buoyancy.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& transform = buoyancy.connectedEntity.getComponent<TransformComponent>();

				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				{
					buoyancy.liquidDensity += 1.0f;
				}
				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
				{
					buoyancy.liquidDensity = (buoyancy.liquidDensity <= 0) ? 0 : (buoyancy.liquidDensity - 1.0f);
				}

				Vector3 relativePosition = transform.position - buoyancyTransform.position;
				float depth = glm::length(relativePosition);
				if (depth > 0)
				{

					if (depth <= buoyancy.waterHeight && insindeWater == true)
					{
						transform.position = buoyancy.finalPos;
						forceAcc.ResetAccumulator();
						stopMoving = true;
					}

					if (depth >= buoyancy.waterHeight && stopMoving == false)
					{
						insindeWater = true;
						if (depth > buoyancy.waterHeight && (depth <= (buoyancy.waterHeight + buoyancy.maxDepth)))
						{
							Vector3 force = glm::normalize(relativePosition);
							force *= buoyancy.liquidDensity * buoyancy.volume;
							forceAcc.AddForce(force);
						}
						if (depth > (buoyancy.waterHeight + buoyancy.maxDepth))
						{
							Vector3 force = -glm::normalize(relativePosition);
							force *= buoyancy.liquidDensity * buoyancy.volume;
							forceAcc.AddForce(force);
						}
						buoyancy.finalPos = transform.position;
					}


					/*Vector3 force = -glm::normalize(relativePosition);
					force *= buoyancy.liquidDensity * buoyancy.volume * (depth - buoyancy.maxDepth) / 2 * buoyancy.maxDepth;
					forceAcc.AddForce(force);*/

					Color col = Color(1, 0, 0, 1);

					/*getWorld().data.renderUtil->DrawLine(buoyancyTransform.position, transform.position,
						col);*/
					getWorld().data.renderUtil->DrawSphere(transform.position, buoyancy.radius, Color::Orange);
				}

			}
			getWorld().data.renderUtil->RenderText("Liquid Density : " + std::to_string((int)buoyancy.liquidDensity), 10.0f, 1040.0f, 0.5f, Color(0, 1, 1, 1));
		}
	}
}
