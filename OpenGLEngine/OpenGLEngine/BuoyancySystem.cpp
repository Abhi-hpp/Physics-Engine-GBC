#include "BuoyancySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& waterTransform = e.getComponent<TransformComponent>();

			// Variable to change so the boundary check always works
			buoyancy.waterXWidth = 50.0f;
			buoyancy.waterZWidth = 50.0f;

			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_UP))
			{
				buoyancy.density += 1.0f;
			}

			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_DOWN))
			{
				if (buoyancy.density >= 1.0f)
				{
					buoyancy.density -= 1.0f;
				}
			}

			if (buoyancy.buoyEntity.hasComponent<TransformComponent>())
			{
				auto& buoyTransform = buoyancy.buoyEntity.getComponent<TransformComponent>();

				getWorld().data.renderUtil->DrawLine(Vector3(0.0f, buoyancy.waterHeight + buoyancy.maxDepth, 0.0f), buoyTransform.position,
					Color(1, 0, 0, 1));

				//getWorld().data.renderUtil->DrawSphere(Vector3(0.0f), 30.0f, Color(0, 0, 1, 1));
				getWorld().data.renderUtil->DrawCube(Vector3(0.0f, buoyancy.waterHeight + buoyancy.maxDepth - 15.0f, 0.0f), Vector3(buoyancy.waterXWidth, 30.0f, buoyancy.waterZWidth), Vector3(0, 0, 0), Color(0, 0, 1, 1));

				getWorld().data.renderUtil->RenderText("Water Density: " + std::to_string(buoyancy.density), 50.0f, 1000.0f, 1.0f, Color(0.15, 0.2, 1, 1));

				float depth = buoyTransform.position.y;
				Vector3 force = Vector3(0, 0, 0);

				if (buoyTransform.position.x >= 0 - buoyancy.waterXWidth / 2 &&		// Check if the Buoy actually falls within the water's boundary
					buoyTransform.position.x <= 0 + buoyancy.waterXWidth / 2 &&
					buoyTransform.position.z >= 0 - buoyancy.waterZWidth / 2 &&
					buoyTransform.position.z <= 0 + buoyancy.waterZWidth / 2)
				{
					// If the buoy is not in the water at all
					if (depth >= buoyancy.waterHeight + buoyancy.maxDepth)
					{
						return;
					}

					// If the buoy is fully submerged
					if (depth <= buoyancy.waterHeight - buoyancy.maxDepth)
					{
						force.y = buoyancy.density * buoyancy.volume;
						if (buoyancy.buoyEntity.hasComponent<ForceAccumulatorComponent>())
						{
							buoyancy.buoyEntity.getComponent<ForceAccumulatorComponent>().AddForce(-force);
						}
						return;
					}

					// If the buoy is just partially submerged
					force.y = buoyancy.density * buoyancy.volume *
						(depth - buoyancy.maxDepth - buoyancy.waterHeight) / 2 * buoyancy.maxDepth;
					if (buoyancy.buoyEntity.hasComponent<ForceAccumulatorComponent>())
					{
						buoyancy.buoyEntity.getComponent<ForceAccumulatorComponent>().AddForce(-force);
					}
				}
			}
			
		}
	}
}
