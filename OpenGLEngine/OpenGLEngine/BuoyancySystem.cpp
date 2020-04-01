#include "BuoyancySystem.h"
#include "TransformComponentV2.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<TransformComponentV2>();
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
			Vector3(0, -14, 0),
			Vector3(600, 30, 600),
			Vector3(0, 0, 0),
			Color::Purple
		);

		for (auto e : getEntities())
		{
			auto& buoyancyTransform = e.getComponent<TransformComponentV2>();
			auto& buoyancy = e.getComponent<BuoyancyComponent>();

			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;

			if (buoyancy.connectedEntity.hasComponent<ForceAndTorqueAccumulatorComponent>()
				&& buoyancy.connectedEntity.hasComponent<TransformComponentV2>())
			{
				auto& forceAcc = buoyancy.connectedEntity.getComponent<ForceAndTorqueAccumulatorComponent>();
				auto& transform = buoyancy.connectedEntity.getComponent<TransformComponentV2>();

				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				{
					buoyancy.liquidDensity += 1.0f;
				}
				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
				{
					buoyancy.liquidDensity = (buoyancy.liquidDensity <= 0) ? 0 : (buoyancy.liquidDensity - 1.0f);
				}

				Vector3 relativePosition = transform.GetPosition() - buoyancyTransform.GetPosition();
				float depth = glm::length(relativePosition);
				if (depth > 0)
				{

					if (depth <= buoyancy.waterHeight && insindeWater == true)
					{
						transform.SetPosition(buoyancy.finalPos);
						forceAcc.ResetForceAccumulatorY();
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
						buoyancy.finalPos = transform.GetPosition();
					}


					/*Vector3 force = -glm::normalize(relativePosition);
					force *= buoyancy.liquidDensity * buoyancy.volume * (depth - buoyancy.maxDepth) / 2 * buoyancy.maxDepth;
					forceAcc.AddForce(force);*/

					Color col = Color(1, 0, 0, 1);

					/*getWorld().data.renderUtil->DrawLine(buoyancyTransform.position, transform.position,
						col);*/
					//getWorld().data.renderUtil->DrawSphere(transform.GetPosition(), buoyancy.radius, Color::Orange);
				}

			}
			//getWorld().data.renderUtil->RenderText("Liquid Density : " + std::to_string((int)buoyancy.liquidDensity), 10.0f, 1040.0f, 0.5f, Color(0, 1, 1, 1));
		}
	}
}
