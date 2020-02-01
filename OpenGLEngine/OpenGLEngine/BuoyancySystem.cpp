#include "BuoyancySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"
#include "ParticleComponent.h"
#include "GravityForceComponent.h"
namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
		{
			for (auto e : getEntities())
			{
				if (e.hasComponent<BuoyancyComponent>())
				{
					e.getComponent<BuoyancyComponent>().liquidDensity += 5;

					if (e.getComponent<BuoyancyComponent>().liquidDensity >= 10000)
					{
						e.getComponent<BuoyancyComponent>().liquidDensity = 10000;
					}

					currentBuoyancyValue = e.getComponent<BuoyancyComponent>().liquidDensity;
				}
			}
		}

		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			for (auto e : getEntities())
			{
				if (e.hasComponent<BuoyancyComponent>())
				{
					e.getComponent<BuoyancyComponent>().liquidDensity -= 5;

					if (e.getComponent<BuoyancyComponent>().liquidDensity <= 10)
					{
						e.getComponent<BuoyancyComponent>().liquidDensity = 10;
					}

					currentBuoyancyValue = e.getComponent<BuoyancyComponent>().liquidDensity;
				}
			}
		}
			
		for (auto e : getEntities())
		{
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			currentBuoyancyValue = buoyancy.liquidDensity;

			if (e.hasComponent<TransformComponent>())
			{
				auto& transform = e.getComponent<TransformComponent>();

				float depth = transform.position.y;

				if (DEBUG_LOG_LEVEL > 0)
				{
					getWorld().data.renderUtil->DrawCube(Vector3(0, (buoyancy.waterHeight - buoyancy.maxDepth) / 2, -50), Vector3(width * 2, buoyancy.maxDepth, length * 2) , Quaternion(Vector3(1, 1, 1), Vector3(1, 1, 1) ), Color::Blue);
				}

				if (depth >= buoyancy.waterHeight || (transform.position.x >= width + 50 || transform.position.x <= -width - 50) || (transform.position.z >= length + 50 || transform.position.z <= -length - 50))
				{

				}
				else
				{
					Vector3 force(0, 0, 0);

					if (depth <= buoyancy.waterHeight - buoyancy.maxDepth)
					{
						force.y = buoyancy.liquidDensity * buoyancy.volume;
						cout << force.y << endl;

						forceAcc.AddForce(force);
						if (DEBUG_LOG_LEVEL > 0)
						{
							getWorld().data.renderUtil->DrawLine(Vector3(transform.position.x, buoyancy.waterHeight, transform.position.z), transform.position, Color::Red);
						}
					}
					else
					{
						float scale = depth + buoyancy.maxDepth <= 1 ? 1 : depth + buoyancy.maxDepth;

						force.y = buoyancy.liquidDensity / (scale - buoyancy.waterHeight) * buoyancy.volume;
						cout << force.y << endl;

						forceAcc.AddForce(force);

						if (DEBUG_LOG_LEVEL > 0)
						{
							getWorld().data.renderUtil->DrawLine(Vector3(transform.position.x, buoyancy.waterHeight, transform.position.z), transform.position, Color::Green);
						}
					}
				}
			}
		}
	}
}
