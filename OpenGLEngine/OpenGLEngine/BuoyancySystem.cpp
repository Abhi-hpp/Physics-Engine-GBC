#include "BuoyancySystem.h"
#include "GravityForceComponent.h"
#include "ParticleComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& liquid = e.getComponent<BuoyancyComponent>().liquid;
			auto& liquidTransform = liquid.getComponent<TransformComponent>();
			auto& entityTransform = e.getComponent<TransformComponent>();
			auto& entity = e.getComponent<BuoyancyComponent>();

			Vector3 force;
			float amountSubmerged = (entityTransform.position.y - entity.maxDepth - liquidTransform.position.y) / (2 * entity.maxDepth);

			force = Vector3(0, 0, 0);

			if (entityTransform.position.y >= liquidTransform.position.y + entity.maxDepth
				|| entityTransform.position.x > liquidTransform.position.x + liquidTransform.scale.x * 0.5
				|| entityTransform.position.x < liquidTransform.position.x - liquidTransform.scale.x * 0.5
				|| entityTransform.position.z > liquidTransform.position.z + liquidTransform.scale.z * 0.5
				|| entityTransform.position.z < liquidTransform.position.z - liquidTransform.scale.z * 0.5)
			{
				force = Vector3(0, 0, 0);
			}
			else if (entityTransform.position.y <= liquidTransform.position.y - entity.maxDepth)
			{
				force.y = entity.volume * entity.liquidDensity;
			}
			else
			{
				force.y = amountSubmerged * entity.volume * entity.liquidDensity;
			}

			e.getComponent<ForceAccumulatorComponent>().AddForce(force);

			// Controls
			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;
			Camera& camera = getWorld().data.renderUtil->camera;

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				entity.liquidDensity++;
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && entity.liquidDensity > 1)
				entity.liquidDensity--;

			static int oldState = GLFW_RELEASE;
			int newState = glfwGetKey(window, GLFW_KEY_SPACE);

			if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
			{
				//bungee.addComponent<BungeeComponent>(10, 20, entityA, entityB);

				auto& world = getWorld();
				auto entity = world.createEntity();
				entity.addComponent<TransformComponent>(Vector3(camera.Position.x, camera.Position.y, -50));
				entity.addComponent<ParticleComponent>(Vector3(0, 0, 0));
				entity.addComponent<ForceAccumulatorComponent>();
				entity.addComponent<GravityForceComponent>(0.1);

				entity.addComponent<BuoyancyComponent>(50, 1, 50, liquid);
			}
			oldState = newState;

			if (DEBUG_LOG_LEVEL > 0)
			{
				int yPos = liquidTransform.position.y - liquidTransform.scale.y * 0.5;
				Vector3 pos = Vector3(liquidTransform.position.x, yPos, liquidTransform.position.z);
				getWorld().data.renderUtil->DrawCube(pos, liquidTransform.scale, Vector3(0, 0, 0), Color(0, 1, 50 / entity.liquidDensity));
			}
		}
	}
}
