#include "BuoyancySystem.h"
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
	Vector3 waterVolume = Vector3(300, 300, 300);
	float liquidDensity = 40.0f;
	void BuoyancySystem::Update(float deltaTime)
	{
		GLFWwindow* window = getWorld().data.renderUtil->window->glfwWindow;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			auto buoyant = getWorld().createEntity();

			buoyant.addComponent<TransformComponent>(Vector3(0, 10, 0), Vector3(5, 5, 5), Vector3(0, 0, 0));
			buoyant.addComponent<ParticleComponent>(Vector3(0, 10, 0), Color::Green);
			buoyant.addComponent<GravityForceComponent>();
			buoyant.addComponent<ForceAccumulatorComponent>();
			buoyant.addComponent<BuoyancyComponent>(1.0f, 1.0f);
		}	
		for (auto e : getEntities())
		{
			Vector3 position = e.getComponent<TransformComponent>().position;

			if ((position.x > -waterVolume.x * 0.5 && position.x < waterVolume.x * 0.5)
				&& (position.y > -waterVolume.y * 0.5 && position.y < waterVolume.y * 0.5)
				&& (position.z > -waterVolume.z * 0.5 && position.z < waterVolume.z * 0.5))
			{
				auto& buoyant = e.getComponent<BuoyancyComponent>();
				auto& buoyantObjTrans = e.getComponent <TransformComponent>();
				auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
		
				Vector3 force(0, 0.1f, 0);
				float depth = abs(buoyantObjTrans.position.y - waterVolume.y * 0.5);


				if (depth >= buoyant.maxDepth)
				{
					force.y = liquidDensity * buoyant.volume;
				}
				else
				{
					float depthRatio = depth / buoyant.maxDepth;
					force.y = liquidDensity * depthRatio * buoyant.volume;

				}
				forceAcc.AddForce(force);
			}
		}
		getWorld().data.renderUtil->DrawCube(Vector3(0, 0, 0), Vector3(50, 50, 50), glm::quat(0, 0, 0, 0), Color::Blue); // Buoyancy volume "water"

	}
};

