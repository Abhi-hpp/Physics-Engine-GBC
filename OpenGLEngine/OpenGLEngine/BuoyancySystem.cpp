#include "BuoyancySystem.h"
#include "TransformComponentV2.h"
#include "ForceAccumulatorComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

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
			auto& waterTransform = e.getComponent<TransformComponentV2>();

			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_UP))
			{
				buoyancy.density += 1.0f;
			}
			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_DOWN))
			{
				buoyancy.density -= 1.0f;
				if (buoyancy.density <= 0.0f)
					buoyancy.density = 0.0f;
			}

			if (buoyancy.buoyEntity.hasComponent<TransformComponentV2>())
			{
				auto& buoyTransform = buoyancy.buoyEntity.getComponent<TransformComponentV2>();

				getWorld().data.renderUtil->DrawLine(Vector3(0.0f, buoyancy.waterHeight + buoyancy.maxDepth, 0.0f), buoyTransform.GetPosition(),
					Color(1, 0, 0, 1));

				//getWorld().data.renderUtil->DrawSphere(Vector3(0.0f), 30.0f, Color(0, 0, 1, 1));
				getWorld().data.renderUtil->DrawCube(Vector3(0.0f, buoyancy.waterHeight + buoyancy.maxDepth - 15.0f, 0.0f), Vector3(50.0f, 30.0f, 50.0f), Vector3(0, 0, 0), Color(0, 0, 1, 1));

				getWorld().data.renderUtil->RenderText(std::to_string(buoyancy.density), 0.0f, 0.0f, 1.0f, Color(1, 1, 1, 1));

				//float depth = buoyTransform.position.y;
				float depth = buoyTransform.GetPosition().y;
				Vector3 force = Vector3(0, 0, 0);

				if (depth >= buoyancy.waterHeight + buoyancy.maxDepth)
				{
					return;
				}

				if (depth <= buoyancy.waterHeight - buoyancy.maxDepth)
				{
					force.y = buoyancy.density * buoyancy.volume;
					if (buoyancy.buoyEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
					{
						buoyancy.buoyEntity.getComponent<ForceAndTorqueAccumulatorComponent>().AddForce(-force);
					}
					return;
				}
				
				force.y = buoyancy.density * buoyancy.volume *
					(depth - buoyancy.maxDepth - buoyancy.waterHeight) / 2 * buoyancy.maxDepth;
				if (buoyancy.buoyEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
				{
					buoyancy.buoyEntity.getComponent<ForceAndTorqueAccumulatorComponent>().AddForce(-force);
				}

			}
			
		}
	}
}
